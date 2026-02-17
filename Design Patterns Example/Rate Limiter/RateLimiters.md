# Rate Limiter Concepts

## 1. TOKEN_BUCKET

Allows requests as long as there are tokens in the bucket. Tokens are added at a fixed rate (refill rate). Each request consumes one token. If the bucket is empty, requests are denied. This enables burst traffic up to the bucket capacity.

**Key Characteristics:**
- Bucket has a maximum capacity
- Tokens refill at a constant rate
- Supports burst traffic
- Simple and memory efficient

**Example:**
```
Bucket Capacity: 10 tokens
Refill Rate: 1 token/second (60 tokens/minute sustained rate)

Time 0s: Bucket has 10 tokens
- 5 requests arrive → 5 tokens consumed → 5 tokens left
Time 5s: Bucket refilled to 10 tokens (5 added + 5 remaining, capped at 10)
- 15 requests arrive → 10 allowed, 5 denied
Time 10s: Bucket refilled to 5 tokens (5 added to the 0 remaining)

Sustained Rate: 60 requests/minute (1 token/sec)
Burst Capacity: Up to 10 requests instantly (if bucket is full)
```

**Advantages:**
- ✅ Handles burst traffic smoothly
- ✅ Memory efficient (only stores token count and timestamp)
- ✅ Simple implementation
- ✅ Provides flexibility for temporary spikes

**Disadvantages:**
- ❌ May allow bursts that overwhelm downstream services
- ❌ Difficult to tune parameters (bucket size, refill rate)
- ❌ Can be exploited if not configured properly

**Use Cases:** API rate limiting with burst allowance, network traffic shaping

---

## 2. FIXED_WINDOW

Divides time into fixed intervals (windows). Counts requests in each window. If the count exceeds the limit, further requests are denied until the next window starts. Simple implementation but can allow traffic bursts at window boundaries.

**Key Characteristics:**
- Time divided into fixed-size windows (e.g., 1 minute)
- Counter resets at window boundary
- Simple to implement
- Can allow 2x traffic at window edges

**Example:**
```
Limit: 10 requests per minute
Window: 0:00 - 0:59, 1:00 - 1:59

Time 0:00-0:59 (Window 1):
- 10 requests arrive at 0:50 → All allowed (counter = 10)

Time 1:00-1:59 (Window 2):
- Counter resets to 0
- 10 requests arrive at 1:05 → All allowed (counter = 10)

Result: 20 requests in 15 seconds (0:50-1:05) were allowed!
```

**Advantages:**
- ✅ Very simple to implement
- ✅ Low memory footprint (single counter per window)
- ✅ Easy to understand and debug
- ✅ Works well with distributed systems (atomic counters)

**Disadvantages:**
- ❌ Allows burst at window boundaries (up to 2x limit)
- ❌ Spike in traffic can occur when window resets
- ❌ Not accurate for strict rate limiting requirements
- ❌ Unfair to users making requests near window end

**Use Cases:** Simple rate limiting scenarios, basic API throttling

---

## 3. SLIDING_WINDOW_LOGS

Keeps a log of timestamps for each request. For a new request, removes timestamps older than the window, then checks if the count within the window exceeds the limit. Most accurate but uses more memory.

**Key Characteristics:**
- Stores timestamp of each request
- Precise and accurate
- No burst issues at boundaries
- Higher memory consumption

**Example:**
```
Limit: 5 requests per minute
Log: [timestamps of requests]

Time 0:10 → Request arrives
  Log: [0:10]
  Count in last 60s: 1 → Allow

Time 0:30 → 4 more requests arrive
  Log: [0:10, 0:30, 0:30, 0:30, 0:30]
  Count in last 60s: 5 → Allow all

Time 0:40 → Request arrives
  Log: [0:10, 0:30, 0:30, 0:30, 0:30]
  Count in last 60s: 5 → Deny

Time 1:15 → Request arrives
  Remove timestamps < 0:15
  Log: [0:30, 0:30, 0:30, 0:30, 1:15]
  Count in last 60s: 5 → Allow
```

**Advantages:**
- ✅ Most accurate rate limiting
- ✅ No boundary issues
- ✅ Fair distribution of requests
- ✅ Precise control over rate

**Disadvantages:**
- ❌ High memory consumption (O(n) where n = number of requests)
- ❌ Performance overhead (cleaning old logs)
- ❌ Not scalable for high-traffic systems
- ❌ Expensive in distributed environments

**Use Cases:** Scenarios requiring precise rate limiting, critical APIs

---

## 4. SLIDING_WINDOW_COUNTER

Splits the window into smaller segments (buckets). Counts requests in each bucket. For a new request, sums counts from relevant buckets to estimate usage in the sliding window. Balances accuracy and memory usage.

**Key Characteristics:**
- Combines Fixed Window and Sliding Window approaches
- Uses weighted calculation for current window
- Good balance between accuracy and efficiency
- Lower memory than Sliding Window Logs

**Example:**
```
Limit: 10 requests per minute
Current time: 1:15 (15 seconds into current window)

Previous Window (0:00-1:00): 8 requests
Current Window (1:00-2:00): 5 requests

Calculation:
Weight of previous window = (60-15)/60 = 0.75
Estimated count = (8 × 0.75) + 5 = 6 + 5 = 11

Result: 11 > 10 → Deny request

At 1:50:
Weight of previous window = (60-50)/60 = 0.167
Estimated count = (8 × 0.167) + 5 = 1.33 + 5 = 6.33
Result: 6.33 < 10 → Allow request
```

**Advantages:**
- ✅ Better accuracy than Fixed Window
- ✅ Low memory usage (only 2 counters)
- ✅ Smooth rate limiting without boundary spikes
- ✅ Good for distributed systems
- ✅ Balances performance and accuracy

**Disadvantages:**
- ❌ Not as precise as Sliding Window Logs
- ❌ Uses approximation (weighted calculation)
- ❌ Slightly more complex than Fixed Window
- ❌ May still allow some burst traffic

**Use Cases:** High-traffic APIs, distributed systems requiring efficiency
