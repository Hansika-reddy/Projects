#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <map>
using namespace std;
class Song {
public:
    string title;
    Song* next;
    Song* prev;

    // Constructor
    Song(const string& t) {
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

    void addSong(const string& title) {
        Song* newSong = new Song(title);
        if (!head) {
            head = tail = current = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
    }

    string playNext() {
        if (current && current->next) {
            current = current->next;
            return current->title;
        }
        return "";
    }

    string playPrev() {
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
    stack<Song*> history;
    map<string, queue<Song*>> playlists;

public:
    void addSong(const string& title) {
        songs.addSong(title);
    }

    void playNext() {
        if (songs.current) {
            history.push(songs.current);
            string nextSong = songs.playNext();
            if (!nextSong.empty()) {
                cout << "Playing: " << nextSong << endl;
            } else {
                cout << "No next song available." << endl;
            }
        }
    }

    void playPrev() {
        if (!history.empty()) {
            songs.current = history.top();
            history.pop();
            cout << "Playing: " << songs.current->title << endl;
        } else {
            cout << "No previous song available." << endl;
        }
    }

    void createPlaylist(const string& playlistName) {
        if (playlists.find(playlistName) == playlists.end()) {
            playlists[playlistName] = queue<Song*>();
            cout << "Playlist '" << playlistName << "' created." << endl;
        } else {
            cout << "Playlist '" << playlistName << "' already exists." << endl;
        }
    }

    void addToPlaylist(const string& playlistName, const string& title) {
        if (playlists.find(playlistName) != playlists.end()) {
            Song* newSong = new Song(title);
            playlists[playlistName].push(newSong);
            cout << "Song '" << title << "' added to playlist '" << playlistName << "'." << endl;
        } else {
            cout << "Playlist '" << playlistName << "' does not exist." << endl;
        }
    }

    void removeFromPlaylist(const string& playlistName) {
        if (playlists.find(playlistName) != playlists.end() && !playlists[playlistName].empty()) {
            Song* songToRemove = playlists[playlistName].front();
            playlists[playlistName].pop();
            delete songToRemove;  // Free the memory
            cout << "Removed song from playlist '" << playlistName << "'." << endl;
        } else {
            cout << "Playlist '" << playlistName << "' is empty or does not exist." << endl;
        }
    }

    void playFromPlaylist(const string& playlistName) {
        if (playlists.find(playlistName) != playlists.end() && !playlists[playlistName].empty()) {
            Song* nextInQueue = playlists[playlistName].front();
            playlists[playlistName].pop();
            cout << "Playing from playlist '" << playlistName << "': " << nextInQueue->title << endl;
            delete nextInQueue;  // Free the memory
        } else {
            cout << "Playlist '" << playlistName << "' is empty or does not exist." << endl;
        }
    }
};

int main() {
    MusicPlayer player;
    int choice;
    string title;
    string playlistName;

    while (true) {
        cout << "Choose from the options below:\n";
        cout << "1: Add Song\n";
        cout << "2: Play Next\n";
        cout << "3: Play Previous\n";
        cout << "4: Create Playlist\n";
        cout << "5: Add to Playlist\n";
        cout << "6: Remove from Playlist\n";
        cout << "7: Play from Playlist\n";
        cout << "8: Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();  // Ignore newline character left in the buffer

        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                getline(cin, title);
                player.addSong(title);
                break;
            case 2:
                player.playNext();
                break;
            case 3:
                player.playPrev();
                break;
            case 4:
                cout << "Enter playlist name: ";
                getline(cin, playlistName);
                player.createPlaylist(playlistName);
                break;
            case 5:
                cout << "Enter playlist name: ";
                getline(cin, playlistName);
                cout << "Enter song title to add to playlist: ";
                getline(cin, title);
                player.addToPlaylist(playlistName, title);
                break;
            case 6:
                cout << "Enter playlist name: ";
                getline(cin, playlistName);
                player.removeFromPlaylist(playlistName);
                break;
            case 7:
                cout << "Enter playlist name: ";
                getline(cin, playlistName);
                player.playFromPlaylist(playlistName);
                break;
            case 8:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid command. Please try again." << endl;
                break;
        }
    }

    return 0;
}

     

 
