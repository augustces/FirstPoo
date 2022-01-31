#include <iostream>
#include <map>
#include <set>
#include <string>
#include <exception>
#include <list>
#include <sstream>

class Tweet {
    int id;
    std::set<std::string> likes;
    std::string msg;
    std::string username;
    Tweet* rt{nullptr};
    bool deleted{false};
    public:
    Tweet (int id = 0, std::string username = "", std::string msg = "");
    void like (std::string username);
    std::set<std::string> getLikes();
    void setRt(Tweet* tw);
    bool isDeleted();
    void setDeleted();
    std::string getMsg();
    std::string getSender();
    int getId();
    friend std::ostream& operator<<(std::ostream& os, Tweet* msg);
    ~Tweet();
};

class Inbox {
    std::map<int, Tweet*> timeline;
    std::map<int, Tweet*> myTweets;
    public:
    Inbox();
    void storeInTimeline(Tweet* tweet);
    std::list<Tweet*> getTimeline();
    Tweet* getTweet(int id);
    void storeInMyTweets (Tweet* tweet);
    std::list<Tweet*> getMyTweets();
    void rmMsgsFrom(std::string username);
    friend std::ostream& operator<< (std::ostream& os, Inbox* in);
    ~Inbox();
};

class User {
    std::map<std::string, User*> followers;
    std::map<std::string, User*> following;
    Inbox inbox;
    std::string username;
    public:
    User (std::string id);
    void follow(User* other);
    Inbox* getInbox();
    void like (int twId);
    void sendTweet(Tweet* tw);
    void unfollow(std::string username);
    void unfollowAll();
    void rejectAll();
    friend std::ostream& operator<<(std::ostream& os, User* user);
    ~User();
};

class Controller {
    int nextTwId{0};
    std::map<int, Tweet*> tweets;
    std::map<std::string, User*> users;
    public:
    Controller();
    void addUser(std::string username);
    Tweet* createTweet(std::string username, std::string msg);
    User* getUser(std::string username);
    void sendRt(std::string username, int twId, std::string rtMsg);
    void rmUser(std::string username);
    void sendTweet(std::string username, std::string msg);
    friend std::ostream& operator<<(std::ostream& os, Controller* cont);
    ~Controller();
};