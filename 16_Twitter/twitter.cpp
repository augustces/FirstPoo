#include "twitter.hpp"

//Tweet
Tweet::Tweet (int id, std::string username, std::string msg) {
    this->id = id;
    this->username = username;
    this->msg = msg;   
}

int Tweet::getId() {
    return id;
}

std::string Tweet::getSender() {
    return this->username;
}

std::string Tweet::getMsg() {
    return this->msg;
}

std::ostream& operator<<(std::ostream& os, Tweet* msg) {
    os << msg->getId() << ":" <<msg->username;
    os << " (" << msg->msg << " ) ";
    if (!(msg->likes.empty())) {
        os << "[ ";
        for (auto l : msg->likes) {
            os << l << " ";
        }
        os << "]";
    }
    os << '\n';
    if (msg->rt != nullptr) {
        os << "     " << msg->rt << '\n';
    }
    return os;
}
//
void Tweet::like (std::string username) {
    likes.insert(likes.end(), username);
}

std::set<std::string> Tweet::getLikes() {
    return this->likes;
}
//
void Tweet::setRt(Tweet* tw) {
    this->rt = tw;
}
//
void Tweet::setDeleted() {
    this->deleted = true;
    this->username = "";
    this->msg = "esse tweet foi deletado";
    this->likes.clear();
}

bool Tweet::isDeleted() {
    return this->deleted;
}

Tweet::~Tweet() {
    delete this->rt;
}

//Inbox
Inbox::Inbox() {}
//
std::list<Tweet*> Inbox::getTimeline () {
    std::list<Tweet*> lista;

    for (auto i : this->timeline) {
        lista.push_front(i.second);
    }
    return lista;
}
//
Tweet* Inbox::getTweet(int id) {
    auto it = this->timeline.find(id);
    if (it == timeline.end())
        throw std::runtime_error("fail: tweet nao existe");
    return it->second;
}

std::list<Tweet*> Inbox::getMyTweets() {
    std::list<Tweet*> lista;

    for (auto i : this->myTweets) {
        lista.push_front(i.second);
    }
    return lista;
}
//
void Inbox::storeInTimeline(Tweet* tweet) {
    this->timeline.insert(std::make_pair(tweet->getId(), tweet));
}

void Inbox::storeInMyTweets (Tweet* tweet) {
    this->myTweets.insert(std::make_pair(tweet->getId(), tweet));
    this->timeline.insert(std::make_pair(tweet->getId(), tweet));
}

void Inbox::rmMsgsFrom(std::string username) {
    std::set<int> ids;
    for (auto& obj : this->timeline) {
        if (obj.second->getSender() == username)
            ids.insert(obj.first);
    }
    for (int it : ids) {
        this->timeline.erase(it);
    }
}

Inbox::~Inbox() {
    for (auto i : timeline) {
        delete i.second;
    }
}

std::ostream& operator<< (std::ostream& os, Inbox* in) {
    auto lista = in->getTimeline();
    for (auto obj : lista) {
        if (!(obj->isDeleted()))
            os << obj;
    }
    return os;
}

//User
User::User (std::string id) {
    this->username = id;
}

void User::follow(User* other) {
    if (this->username == other->username)
        throw std::runtime_error("fail: impossivel seguir a si proprio");

    if (this->following.find(other->username) != this->following.end())
        throw std::runtime_error("fail: usuario ja é seguido");
    this->following.insert(std::make_pair(other->username, other));
    
    other->followers.insert(std::make_pair(this->username, this));
}

Inbox* User::getInbox() {
    return &inbox;
}

void User::like (int twId) {
    auto it = this->inbox.getTweet(twId);
    it->like(this->username);
}

void User::sendTweet(Tweet* tw) {
    this->inbox.storeInMyTweets(tw);
    for (auto i : this->followers) {
        auto other = i.second->getInbox();
        other->storeInTimeline(tw);
    }
}

void User::unfollow(std::string username) {
    auto it = this->following.find(username);
    if (it == this->following.end())
        throw std::runtime_error("fail: user nao encontrado");

    this->inbox.rmMsgsFrom(username);

    it->second->followers.erase(this->username);
    this->following.erase(username);
}

void User::unfollowAll() {
    if (this->following.empty())
        return;
    auto cop = this->following;
    for (auto it : cop) {
        this->unfollow(it.first);
    }
}

void User::rejectAll() {
    if ((this->followers.empty()))
        return;
    auto cop = this->followers;
    for(auto obj : cop) {
        obj.second->unfollow(this->username);
    }
}

User::~User() {
    for (auto i : followers) {
        delete i.second;
    }
    for (auto i : following) {
        delete i.second;
    }
}

std::ostream& operator<<(std::ostream& os, User* user) {
    os << user->username << '\n';
    os << "     seguidos    [ ";
    for (auto s : user->following) {
        os << s.first << " ";
    }
    os << "]\n";

    os << "     seguidores [ ";
    for (auto s : user->followers) {
        os << s.first << " ";
    }
    os << "]\n";
    return os;
}

//Controller
Controller::Controller (){}

void Controller::addUser(std::string username) {
    auto it =   users.find(username);

    if (it != users.end())
        throw std::runtime_error("fail: user ja existe");
    
    User* u = new User(username);
    users.insert(std::make_pair(username, u));
}

User* Controller::getUser(std::string username) {
    auto it = users.find(username);

    if (it == users.end())
        throw std::runtime_error("fail: user nao encontrado");

    return it->second;
}

Tweet* Controller::createTweet(std::string username, std::string msg){
    Tweet* m = new Tweet (nextTwId, username, msg);
    return m;
}

void Controller::sendRt(std::string username, int twId, std::string rtMsg) {
    auto it = this->tweets.find(twId);
    if (it == this->tweets.end())
        throw std::runtime_error("fail: tweet nao existe");
    auto user = this->getUser(username);
    auto rt = this->createTweet(username, rtMsg);
    rt->setRt(it->second);
    this->tweets.insert(std::make_pair(nextTwId, rt));    
    user->sendTweet(rt);
    nextTwId++;
}

void Controller::rmUser(std::string username) {
    auto user = this->getUser(username);
    
    auto tws = user->getInbox()->getMyTweets();
    for (auto& tw : tws) {
        if (!(tw->isDeleted()))
            tw->setDeleted();
    }
    user->unfollowAll();
    user->rejectAll();
    
    this->users.erase(username);
}

void Controller::sendTweet(std::string username, std::string msg) {
    auto it = getUser(username);
    auto m = createTweet(username, msg);
    this->tweets.insert(std::make_pair(nextTwId, m));
    nextTwId++;
    it->sendTweet(m);
}

Controller::~Controller () {
    for (auto i : tweets) {
        delete i.second;
    }
    for (auto i : users) {
        delete i.second;
    }
}

std::ostream& operator<<(std::ostream& os, Controller* cont) {
    for (auto u : cont->users) {
        os << u.second << '\n';
    }
    return os;
}