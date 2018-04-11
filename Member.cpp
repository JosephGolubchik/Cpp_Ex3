#include "Member.h"

int Member::numOfMembers = 0; // number of existing members

int Member::numFollowers(){ // number of followers a memeber has
    return numOfFollowers; 
}

int Member::numFollowing(){ // number of members a member is following
    return numOfFollowing;
}


void Member::follow(Member& member){ // follow a member
    if(!isFollowing(&member)&&(this != &member)){
        numOfFollowing++; 
        member.numOfFollowers++;
        following.push_back(&member);
        member.followers.push_back(this);
    }
}
    
void Member::unfollow(Member& member){ // unfollow a member given a reference 
    if(isFollowing(&member)){
        numOfFollowing--; 
        member.numOfFollowers--;
        tempUnfollow(&member, following);
        tempUnfollow(this, (&member)->followers);
    }
}
    
void Member::unfollow(Member* member){ // unfollow a member given a pointer
    if(isFollowing(member)){
        numOfFollowing--; 
        member->numOfFollowers--;
        tempUnfollow(member, following);
        tempUnfollow(this, member->followers);
    }
}
    
bool Member::compare(Member* a, Member* b){ // check if two pointers are pointing to the same member
    return a == b;
}

bool Member::isFollowing(Member* member){ // checks if a memeber is following another member
    bool ans = false;
    for (vector<Member*>::iterator it = following.begin(); it != following.end(); ++it){
        if(compare(*it, member)) ans = true;
    }
    return ans;
}

bool Member::isFollowedBy(Member* member){ // checks if a member is being followed by another memeber
    bool ans = false;
    for (vector<Member*>::iterator it = followers.begin(); it != followers.end(); ++it){
        if(compare(*it, member)) ans = true;
    }
    return ans;
}

void Member::tempUnfollow(Member* member, vector<Member*>& vect){ // searches for a certain member in a vector and erases it
    for(vector<Member*>::iterator it = vect.begin(); it != vect.end(); ++it){
		if(compare(*it, member)) {
			it = vect.erase(it);
			return;
		} 
    }
}


void Member::unFollowAll(){
    int N = following.size(); // number of members we are following
    for (int i = 0; i < N; i++) { 
        this->unfollow(following[0]);
    }

}

void Member::deleteAllFollowers(){ // unfollowed all that were followed, used in destructor
    int N = followers.size(); // number of members following us
    for (int i = 0; i < N; i++) { 
        followers[i]->unfollow(this);
    }
}

Member::Member(){ // constructor
    numOfFollowers = 0;
    numOfFollowing = 0;
    numOfMembers++;
}

Member::~Member(){ // destructor
    unFollowAll(); 
    deleteAllFollowers();
    numOfMembers--;
}

    
