#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <map>

class Song {
public:
    std::string title;
    Song* next;
    Song* prev;

    // Constructor
    Song(const std::string& t) {
        title = t;
        next = nullptr;
        prev = nullptr;
    }
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
    std::map<std::string, std::queue<Song*>> playlists;

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

    void createPlaylist(const std::string& playlistName) {
        if (playlists.find(playlistName) == playlists.end()) {
            playlists[playlistName] = std::queue<Song*>();
            std::cout << "Playlist '" << playlistName << "' created." << std::endl;
        } else {
            std::cout << "Playlist '" << playlistName << "' already exists." << std::endl;
        }
    }

    void addToPlaylist(const std::string& playlistName, const std::string& title) {
        if (playlists.find(playlistName) != playlists.end()) {
            Song* newSong = new Song(title);
            playlists[playlistName].push(newSong);
            std::cout << "Song '" << title << "' added to playlist '" << playlistName << "'." << std::endl;
        } else {
            std::cout << "Playlist '" << playlistName << "' does not exist." << std::endl;
        }
    }

    void removeFromPlaylist(const std::string& playlistName) {
        if (playlists.find(playlistName) != playlists.end() && !playlists[playlistName].empty()) {
            Song* songToRemove = playlists[playlistName].front();
            playlists[playlistName].pop();
            delete songToRemove;  // Free the memory
            std::cout << "Removed song from playlist '" << playlistName << "'." << std::endl;
        } else {
            std::cout << "Playlist '" << playlistName << "' is empty or does not exist." << std::endl;
        }
    }

    void playFromPlaylist(const std::string& playlistName) {
        if (playlists.find(playlistName) != playlists.end() && !playlists[playlistName].empty()) {
            Song* nextInQueue = playlists[playlistName].front();
            playlists[playlistName].pop();
            std::cout << "Playing from playlist '" << playlistName << "': " << nextInQueue->title << std::endl;
            delete nextInQueue;  // Free the memory
        } else {
            std::cout << "Playlist '" << playlistName << "' is empty or does not exist." << std::endl;
        }
    }
};

int main() {
    MusicPlayer player;
    int choice;
    std::string title;
    std::string playlistName;

    while (true) {
        std::cout << "Choose from the options below:\n";
        std::cout << "1: Add Song\n";
        std::cout << "2: Play Next\n";
        std::cout << "3: Play Previous\n";
        std::cout << "4: Create Playlist\n";
        std::cout << "5: Add to Playlist\n";
        std::cout << "6: Remove from Playlist\n";
        std::cout << "7: Play from Playlist\n";
        std::cout << "8: Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore();  // Ignore newline character left in the buffer

        switch (choice) {
            case 1:
                std::cout << "Enter song title: ";
                std::getline(std::cin, title);
                player.addSong(title);
                break;
            case 2:
                player.playNext();
                break;
            case 3:
                player.playPrev();
                break;
            case 4:
                std::cout << "Enter playlist name: ";
                std::getline(std::cin, playlistName);
                player.createPlaylist(playlistName);
                break;
            case 5:
                std::cout << "Enter playlist name: ";
                std::getline(std::cin, playlistName);
                std::cout << "Enter song title to add to playlist: ";
                std::getline(std::cin, title);
                player.addToPlaylist(playlistName, title);
                break;
            case 6:
                std::cout << "Enter playlist name: ";
                std::getline(std::cin, playlistName);
                player.removeFromPlaylist(playlistName);
                break;
            case 7:
                std::cout << "Enter playlist name: ";
                std::getline(std::cin, playlistName);
                player.playFromPlaylist(playlistName);
                break;
            case 8:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid command. Please try again." << std::endl;
                break;
        }
    }

    return 0;
}

