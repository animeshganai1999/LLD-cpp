#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Target interface - What client expects
class MediaPlayer {
public:
    virtual void play(string audioType, string fileName) = 0;
    virtual ~MediaPlayer() = default;
};  

// Adaptee interface - Existing interface that needs to be adapted
class AdvancedMediaPlayer {
public:
    virtual void playVlc(string fileName) = 0;
    virtual void playMp4(string fileName) = 0;
    virtual ~AdvancedMediaPlayer() = default;
};

// Concrete Adaptee - Implements the AdvancedMediaPlayer interface
class VlcPlayer : public AdvancedMediaPlayer {
public:
    void playVlc(string fileName) override {
        cout << "Playing vlc file. Name: " << fileName << endl;
    }
    void playMp4(string fileName) override {
        // Do nothing
    }
};

// Another Concrete Adaptee
class Mp4Player : public AdvancedMediaPlayer {  
public:
    void playVlc(string fileName) override {
        // Do nothing
    }
    void playMp4(string fileName) override {
        cout << "Playing mp4 file. Name: " << fileName << endl;
    }
};

// Adapter class - Implements the Target interface and uses an Adaptee
class MediaAdapter : public MediaPlayer{
private:
    AdvancedMediaPlayer* advancedMusicPlayer;
public:
    MediaAdapter(string audioType){
        if(audioType == "vlc" ){
            advancedMusicPlayer = new VlcPlayer();
        }
        else if (audioType == "mp4"){
            advancedMusicPlayer = new Mp4Player();
        }
    }
    
    void play(string audioType, string fileName) override {
        if(audioType == "vlc"){
            advancedMusicPlayer->playVlc(fileName);
        }
        else if(audioType == "mp4"){
            advancedMusicPlayer->playMp4(fileName);
        }
    }
    ~MediaAdapter() {
        delete advancedMusicPlayer;
    }
};

// Client class - Uses the Target interface
class AudioPlayer : public MediaPlayer {
private:
    MediaAdapter* mediaAdapter;
public:
    AudioPlayer() : mediaAdapter(nullptr) {}
    void play(string audioType, string fileName) override {
        if(audioType == "mp3"){
            cout << "Playing mp3 file. Name: " << fileName << endl;
        }
        else if(audioType == "vlc" || audioType == "mp4"){
            mediaAdapter = new MediaAdapter(audioType);
            mediaAdapter->play(audioType, fileName);
            delete mediaAdapter;
        }
        else{
            cout << "Invalid media. " << audioType << " format not supported" << endl;
        }
    }
};

int main() {
    AudioPlayer* audioPlayer = new AudioPlayer();
    audioPlayer->play("mp3", "song1.mp3");
    audioPlayer->play("mp4", "video1.mp4");
    audioPlayer->play("vlc", "movie1.vlc");
    audioPlayer->play("avi", "myMovie.avi");
    delete audioPlayer;

    return 0;
}