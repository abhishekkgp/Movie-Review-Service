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

/*
 TIPS:
 1.) Check for corner cases (like 0 is exception case)
 2.) Check for global memory sizes,memory refreshments and its complexity 
 3.) Check for sorting criteria (if used 1-based indexing)
 4.) Check for numbers overflow (while multiplying and doing MOD)
 5.) Check for typecasting issues like int to float( while dividing numbers)
*/
