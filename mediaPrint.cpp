#include "pch.hpp"

std::ifstream key_file("key.json");
json key = json::parse(key_file);

static void mediaPrint() {
    std::string query;
    std::cout << "media name: ";
    std::getline(std::cin, query); //we are basically setting a name for this string the string is query then the string gets it's i guess value based upon our getline which is going to be the name of the media, using getline bc normal string would just return "batman returns" as "batman", so we need the whole line.

    std::string api_key = key["TMDB_KEY"];
    std::string url = "https://api.themoviedb.org/3/search/multi?api_key=" + api_key + "&query=" + cpr::util::urlEncode(query);
    //this part of this code is again the same, setting a string, calling it api_key and we set this key to the tmbi key, next string you can read it's the same thing, string = the url, but here we combine another string "api_key" and then the query result from our first cin line using & (idk why yet i'll look it up) and then the crp util encoder to well i guess encode the query so it doesn't have spaces but i still don't get that part not gonna ask why tho just gonna let it work


    cpr::Response r = cpr::Get(cpr::Url{ url });

    json data = json::parse(r.text);

    json results = data["results"];


    std::cout << "API Response:\n" << r.text << std::endl;

    for (const json item : results) {
        if (item.contains("title")) {
            std::cout << "Movie: " << item["title"] << std::endl;
        }
        else if (item.contains("name")) {
            std::cout << "TV Show / Anime: " << item["name"] << std::endl;
        }
    }
}