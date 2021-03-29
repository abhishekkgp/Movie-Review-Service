/*OVERVIEW:
The movie review service collects reviews for movies from its users. Later these
movie reviews are used to derive insights which helps in enriching the lives of its
customers with entertainment.

Internal Capabilities:
1. Users of the service can review only movies which are released so far, they
cannot review upcoming movies.
2. Users can give a review-score between 1 to 10. (Higher the score the better
the liking for the movie). Currently we are not allowing a user to review the
same movie multiple times.
3. The service by default on-boards a user as a ‘viewer’. Later a ‘viewer’ can
be upgraded to a ‘critic’ after he/she has published more than 3 reviews
for various movies.
4. Critics are considered as experts in the judgement here, so critics reviews
will be captured with more weightage. i.e. 6 review rating of a critic will be
considered as 12 (2x) NOTE: Older reviews by the user as `viewer` shall not
be affected.
5. Good To Have: Based on the users behaviour, the service should give the
capability to plugin more user upgradation policies. Eg. User -> Critic ->
Expert -> Admin.

Requirements
Each of the following features needs to be implemented:
1. Adding users and movies.
2. User to review a movie.
3. List top n movies by total review score by ‘critics’ in a particular genre.
4. Average review score in a particular year of release.
5. Average review score for a particular movie.
Discover your treasures hidden within!

Expectations
1. Make sure that you have working and demonstrable code for all the above
requirements.
2. Feature requirements should be strictly followed. Work on the expected
output first and then add good-to-have features of your own.
3. Use of proper abstraction, separation of concerns is required.
4. Code should easily accommodate new requirements with minimal
changes.
5. Proper exception handling is required.
6. Code should be modular, readable and unit-testable.


Important Notes:
● Do not use any database store, use in-memory data structure.
● Do not write an API on top of the service methods.
● Do not create any UI for the application.
● Do not build a Command line interface, executing test cases or via the
simple Main function should be sufficient.



Sample Test Cases:
1. Onboard 10 movies onto your platform in 3 different years.
a. Add Movie("Don" released in Year 2006 for Genres “Action” &“Comedy”)
b. Add Movie("Tiger" released in Year 2008 for Genre “Drama”)
c. Add Movie("Padmaavat" released in Year 2006 for Genre “Comedy”)
d. Add Movie("Lunchbox" released in Year 2021 for Genre “Drama”)
e. Add Movie("Guru" released in Year 2006 for Genre “Drama”)
f. Add Movie("Metro" released in Year 2006 for Genre “Romance”)

2. Add users to the system:
a. Add User(“SRK”)
b. Add User(“Salman”)
c. Add User(“Deepika”)

3. Add Reviews:
a. add_review(“SRK”, “Don”, 2)
b. add_review(“SRK”, “Padmavaat”, 8)
c. add_review(“Salman”, “Don”, 5)
d. add_review(“Deepika”, “Don”, 9)
e. add_review(“Deepika”, “Guru”, 6)
f. add_review(“SRK”,”Don”, 10) - Exception multiple reviews not allowed Discover your treasures hidden within!
g. add_review(“Deepika”, “Lunchbox”, 5) - Exception movie yet to be released
h. add_review(“SRK”, “Tiger”, 5). Since ‘SRK’ has published 3 reviews, he is promoted to ‘critic’ now.
i. add_review(“SRK”, “Metro”, 7)*/


#include<bits/stdc++.h>
using namespace std;

class MovieList{ //class define
    public:
    string year;
    vector<string> genre; // if particular movie is included in more than 1 genre
    int sum_r;      // to get sum of all rating for particular movie
    int count_r;    //to count number of review


    //for ctitic review
    int sum_critic_r;       // to get sum of all critic rating for particular movie
    int count_critic_r;     //to count number of critic review
};

// to add new movie
void add_movies(string movieName, string year, string genre, unordered_map<string, MovieList> &movies )
{
    if(movies.find(movieName)!=movies.end())
    {
        movies[movieName].genre.push_back(genre);
        return;
    }
    MovieList mv;
    mv.year=year;
    mv.genre.push_back(genre);
    mv.sum_r=0;
    mv.count_r=0;

    mv.sum_critic_r=0;
    mv.count_critic_r=0;
    movies[movieName]=mv;
}

// to add new user
void add_user(string userName, unordered_map<string, vector<string> > &user)
{
    vector<string> temp;
    user[userName]=temp;
}

//checking if person has already reviewed for particular movie or not
bool multiple_r(unordered_map< string , vector<string> > user, string userName, string movieName)
{
    for(auto x: user[userName])
    {
        if(x==movieName)
        {
            return true;
        }
    }
    return false;
}

//checking if user has become critic or not
bool check_critic(unordered_map< string , vector<string> > user, string userName )
{
    if(user[userName].size()>2) return true;
    return false;
}

//Adding review of user
void add_review(string userName, string movieName, float rating,unordered_map<string, MovieList> &movies, unordered_map<string, vector<string> > &user )
{
    //exception cases
    //CASE 1: Allredy reviewed by user for given movie
    if( multiple_r( user,userName, movieName) ) 
    {
        cout<<"Exception multiple reviews not allowed"<<endl;
        return;
    }
    //CASE 2: Movie yet to release
    if(movies[movieName].year> "2020") //assung 2021 has just started 
    {
        cout<<"Exception " <<movieName<<" yet to be released"<<endl;
        return;
    }
     //CASE 3: if user is critic
    if(check_critic(user,userName))
    {
        user[userName].push_back(movieName);

        movies[movieName].sum_r +=rating*2;
        movies[movieName].count_r +=2;

        movies[movieName].sum_critic_r +=rating*2;
        movies[movieName].count_critic_r +=2;
        return;
    }
    
    //In general case
    user[userName].push_back(movieName);

    movies[movieName].sum_r +=rating;
    movies[movieName].count_r +=1;
}

// calculating average review for particular movie
double  Average_review(unordered_map<string, MovieList> movies, string movieName)
{
    int sum=movies[movieName].sum_r;
    int count=movies[movieName].count_r;
    if(count==0)
    {
        cout<<"Movie is not relsesed! so review is:";
    }
    return (double(sum)/double(count));
}

// calculating average critic review for particular movie
double  Average_critic_review(unordered_map<string, MovieList> movies, string movieName)
{
    int sum=movies[movieName].sum_critic_r;
    int count=movies[movieName].count_critic_r;
    
    return (double(sum)/double(count));
}

// fiding is given genre present in string of particlar movie genre
bool find_genre(vector<string> str, string genre)
{
    for(int i=0;i<str.size();i++)
    {
        if(str[i]==genre) return true;
    }
    return false;
}

// finding top movies as per critic review for given genre name
void top_critic_rated_movie( unordered_map<string, MovieList> movies, string genreName, int n)
{
    vector<pair<double,string> > topMovies;
    
    for(auto x: movies)
    {
        if(find_genre(x.second.genre,genreName))
        {
            double rating=Average_critic_review(movies,x.first) ;
            if(rating>0) topMovies.push_back(make_pair(rating, x.first));
            
        }
    }
    if(topMovies.size()==0)
    {
        cout<<"No Critic review for any movie in this genre."<<endl;
        return;
    }
    sort(topMovies.begin(),topMovies.end());
    for(int i=0;i<n && i<topMovies.size();i++)
    {
        cout<<topMovies[i].second<<" ";
    }
    cout<<endl;
    
}

int main() {
    //using Hashing: movies, with key as "Movie Name" and value as define in class MovieList
    unordered_map<string, MovieList> movies;
	add_movies("Don","2006","Action",movies);
	add_movies("Don","2006","Comedy",movies); //as Don is inluded in two genre
    add_movies("Tiger","2008","Drama",movies);
    add_movies("Padmaavat","2006","Comedy",movies);
    add_movies("Lunchbox","2021","Drama",movies);
    add_movies("Guru","2006","Drama",movies);
    add_movies("Metro","2006","Romance",movies);
    
    
    // using hashing naming user which has key as  username and value as name of movies he reviewed
    unordered_map<string, vector<string> > user;
    //adding user name
    add_user("SRK",user);
    add_user("Salman",user);
    add_user("Deepike",user);
    
    // Adding user review
    add_review("SRK","Don",2, movies,user);
    add_review("SRK","Padmavaat",8,movies,user);
    add_review("Salman","Don",5,movies,user);
    add_review("Deepika","Don",9,movies,user);
    add_review("Deepika","Guru",6,movies,user);
    add_review("SRK","Don",10,movies,user);
    add_review("Deepika","Lunchbox",5,movies,user);
    add_review("SRK","Tiger",5,movies,user);
    add_review("SRK","Metro",7,movies,user);
    
    cout<<endl;
    cout<<"Average Review score:"<<endl;
    cout<<"Don: "<<setprecision(2)<<Average_review(movies, "Don")<<endl;
    cout<<"Tiger: "<<setprecision(2)<<Average_review(movies, "Tiger")<<endl;
    cout<<"Metro: "<<setprecision(2)<<Average_review(movies, "Metro")<<endl;
    
    cout<<endl;
    cout<<"Top movies by total review score by ‘critics’ in a particular genre:"<<endl;
    cout<<"Romance: ";
    int n=2; // to get "List top n movies by total review score by ‘critics’ in a particular genre"
    top_critic_rated_movie(movies,"Romance",n);
    
    cout<<"Comedy: ";
    n=2; // to get "List top n movies by total review score by ‘critics’ in a particular genre"
    top_critic_rated_movie(movies,"Comedy",n);

	return 0;
}
