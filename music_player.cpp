#include <iostream>
#include <stack>
#include <queue>
#include <string>

class Song {
public:
    std::string title;
    Song* next;
    Song* prev;

     Song(const std::string& t) : title(t), next(nullptr), prev(nullptr) {}
};
class DoublyLinkedList {
public:
    Song* head;
    Song* tail;
    Song* current;

    DoublyLinkedList() : head(nullptr), tail(nullptr), current(nullptr) {}

    void addSong(const std::string& title) {
        Song* newSong = new Song(title);
        if (!head) {
            head = tail = current = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
    }

    std::string playNext() {
        if (current && current->next) {
            current = current->next;
            return current->title;
        }
        return "";
    }

    std::string playPrev() {
        if (current && current->prev) {
            current = current->prev;
            return current->title;
        }
        return "";
    }
};
class MusicPlayer {
private:
    DoublyLinkedList songs;
    std::stack<Song*> history;
    std::queue<Song*> playlist;

public:
    void addSong(const std::string& title) {
        songs.addSong(title);
    }

    void playNext() {
        if (songs.current) {
            history.push(songs.current);
            std::string nextSong = songs.playNext();
            if (!nextSong.empty()) {
                std::cout << "Playing: " << nextSong << std::endl;
            } else {
                std::cout << "No next song available." << std::endl;
            }
        }
    }

    void playPrev() {
        if (!history.empty()) {
            songs.current = history.top();
            history.pop();
            std::cout << "Playing: " << songs.current->title << std::endl;
        } else {
            std::cout << "No previous song available." << std::endl;
        }
    }

    void addToPlaylist(const std::string& title) {
        Song* newSong = new Song(title);
        playlist.push(newSong);
    }

    void playFromPlaylist() {
        if (!playlist.empty()) {
            Song* nextInQueue = playlist.front();
            playlist.pop();
            std::cout << "Playing from playlist: " << nextInQueue->title << std::endl;
        } else {
            std::cout << "Playlist is empty." << std::endl;
        }
    }
};
int main() {
    MusicPlayer player;
    player.addSong("Song 1");
    player.addSong("Song 2");
    player.addSong("Song 3");

    player.playNext(); 
    player.playNext(); 
    player.playPrev(); 

    player.addToPlaylist("Song 4");
    player.addToPlaylist("Song 5");

    player.playFromPlaylist();
    player.playFromPlaylist(); 

    return 0;
}
