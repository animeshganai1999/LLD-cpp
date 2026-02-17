#include<bits/stdc++.h>
#include<mutex>
#include<chrono>
#include<thread>
using namespace std;

enum class UserTier {
    Free,
    Premium,
    Enterprise
};

enum class RateLimiterType {
    TokenBucket,
    FixedWindow,
    SlidingWindow
};

class RateLimiterConfiguration {
public:
    int maxRequests;
    int timeWindowSeconds;
    RateLimiterConfiguration(int maxReq, int timeWindow) : maxRequests(maxReq), timeWindowSeconds(timeWindow) {}
};

class User {
public:
    string userId;
    UserTier tier;
    User(string id, UserTier tier) : userId(id), tier(tier) {}
};

// RateLimiter interface
class RateLimiter {
protected:
    RateLimiterConfiguration config;
public:
    RateLimiter(RateLimiterConfiguration config) : config(config) {}
    virtual bool allowRequest(string userId) = 0;
};

class TokenBucketRateLimiter : public RateLimiter {
    map<string, int> userTokens; // Placeholder for user tokens
    map<string, time_t> lastRefillTime; // Placeholder for last refill time
    mutex mtx; // Mutex for thread safety
public:
    TokenBucketRateLimiter(RateLimiterConfiguration config) : RateLimiter(config) {}
    bool allowRequest(string userId) override {
        lock_guard<mutex> lock(mtx);
        time_t currentTime = time(nullptr);
        // Refill tokens based on time elapsed
        if(lastRefillTime.find(userId) == lastRefillTime.end()){ // When user is seen for the first time
            lastRefillTime[userId] = currentTime;
            userTokens[userId] = config.maxRequests;
        }else{
            int elapsedTime = currentTime - lastRefillTime[userId];
            int tokensToAdd = (elapsedTime * config.maxRequests) / config.timeWindowSeconds;
            userTokens[userId] = min(config.maxRequests, userTokens[userId] + tokensToAdd);
            lastRefillTime[userId] = currentTime;
        }
        if(userTokens[userId] > 0){
            userTokens[userId]--;
            return true;
        }
        return false;
    }
};

class FixedWindowRateLimiter : public RateLimiter {
    map<string, int> userRequestCount; // Placeholder for user request count
    map<string, chrono::steady_clock::time_point> windowStartTime; // Placeholder for window start time
    mutex mtx; // Mutex for thread safety
public:
    FixedWindowRateLimiter(RateLimiterConfiguration config) : RateLimiter(config) {}
    bool allowRequest(string userId) override {
        lock_guard<mutex> lock(mtx);
        auto now = chrono::steady_clock::now();
        auto windowDuration = chrono::seconds(config.timeWindowSeconds);
        // Check if the user exists or if current window has expired
        if(windowStartTime.find(userId) == windowStartTime.end() || now - windowStartTime[userId] > windowDuration){
            // Start a new window
            windowStartTime[userId] = now;
            userRequestCount[userId] = 1;
            return true;
        }
        // Within the same window, check if we can allow the request
        if(userRequestCount[userId] < config.maxRequests){
            userRequestCount[userId]++;
            return true;
        }
        return false;
    }
};

class SlidingWindowRateLimiter : public RateLimiter {
    map<string, queue<chrono::steady_clock::time_point>> userTimestamps; // Placeholder for user request times
    mutex mtx; // Mutex for thread safety
public:
    SlidingWindowRateLimiter(RateLimiterConfiguration config) : RateLimiter(config) {}
    bool allowRequest(string userId) override {
        lock_guard<mutex> lock(mtx);
        auto now = chrono::steady_clock::now();
        auto windowDuration = chrono::seconds(config.timeWindowSeconds);

        // Get or create timestamp queue for this user
        auto &timestamp = userTimestamps[userId];

        // Remove timestamps outside the current window
        while (!timestamp.empty() && now - timestamp.front() > windowDuration) {
            timestamp.pop();
        }

        // Check if we can allow the request
        if(timestamp.size() < config.maxRequests) {
            timestamp.push(now);
            return true;
        }

        return false;
    }
};

// Factory to create rate limiters based on user tier
class RateLimiterFactory {
public:
    static RateLimiter* createRateLimiter(UserTier tier, RateLimiterConfiguration config) {
        switch (tier) {
            case UserTier::Free:
                return new FixedWindowRateLimiter(config);
            case UserTier::Premium:
                return new TokenBucketRateLimiter(config);
            case UserTier::Enterprise:
                return new SlidingWindowRateLimiter(config);
            default:
                return nullptr;
        }
    }
};

class RateLimiterService{
private:
    map<UserTier, RateLimiter*> rateLimiters;
public:
    RateLimiterService(){
        rateLimiters[UserTier::Free] = RateLimiterFactory::createRateLimiter(UserTier::Free, RateLimiterConfiguration(10, 60));
        rateLimiters[UserTier::Premium] = RateLimiterFactory::createRateLimiter(UserTier::Premium, RateLimiterConfiguration(100, 60));
        rateLimiters[UserTier::Enterprise] = RateLimiterFactory::createRateLimiter(UserTier::Enterprise, RateLimiterConfiguration(1000, 60));
    }
    bool allowRequest(User user){
        RateLimiter* limiter = rateLimiters[user.tier];
        if(limiter == nullptr){
            throw std::runtime_error("No rate limiter found for user tier");
        }
        bool result = limiter->allowRequest(user.userId);
        if(result){
            cout << "Request allowed for user: " << user.userId << endl;
        }else{
            cout << "Request denied for user: " << user.userId << endl;
        }
        return result;
    }
};


int main() {
    User* user1 = new User("user1", UserTier::Free);
    User* user2 = new User("user2", UserTier::Premium);
    User* user3 = new User("user3", UserTier::Enterprise);

    RateLimiterService rateLimiterService;
    for(int i = 0; i < 15; i++){
        cout << "Request " << i+1 << " for user1: " << rateLimiterService.allowRequest(*user1) << endl;
        cout << "Request " << i+1 << " for user2: " << rateLimiterService.allowRequest(*user2) << endl;
        cout << "Request " << i+1 << " for user3: " << rateLimiterService.allowRequest(*user3) << endl;
    }

    delete user1;
    delete user2;
    delete user3;

    return 0;
}