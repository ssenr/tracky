#pragma once

void mediaPrint() {
    std::ifstream key_file("key.json");
    json key = json::parse(key_file);
    std::string query;
    std::cout << "media name: ";
    std::getline(std::cin, query); 
    
    
    //we are basically setting a name for this string the string is query then the string gets it's i guess value based upon our getline which is going to be the name of the media, using getline bc normal string would just return "batman returns" as "batman", so we need the whole line.


    std::string api_key = key["TMDB_KEY"];
    std::string url = "https://api.themoviedb.org/3/search/multi?api_key=" + api_key + "&query=" + cpr::util::urlEncode(query);
        
    
    //this part of this code is again the same, setting a string, calling it api_key and we set this key to the tmbi key, next string you can read it's the same thing, string = the url, but here we combine another string "api_key" and then the query result from our first cin line using & (idk why yet i'll look it up) and then the crp util encoder to well i guess encode the query so it doesn't have spaces but i still don't get that part not gonna ask why tho just gonna let it work
    
    cpr::Response cprMediaResponse = cpr::Get(cpr::Url{url});

    //this is the curl http library thing and just like std:: its set like cpr:: and response is a function kinda like cout, we called it cprMediaResponse, cprMediaResponse also uses the GET function idk what this shit means lowkey can't explain lolxd. but basically we call the string url we defined before. 

    json data = json::parse(cprMediaResponse.text);

    // we set the type to json instead of using auto because apparently auto is a sin. json file data gets prased from that text file we got from the curl

    json results = data["results"];

    // set type to json, look for the arrays in the json file (i think idrk not gonna question it)

    std::cout << "API Response:\n" << cprMediaResponse.text << std::endl;


    for (int i = 0; i < results.size(); ++i) {
        const json& item = results[i];

        std::string title;
        if (item.contains("title")) {
            title = item["title"];
        }
        else if (item.contains("name")) {
            title = item["name"];
        }
        else {
            title = "No TITLE found.";
        }

        std::string releaseDate;
        if (item.contains("release_date")) {
            releaseDate = item["release_date"];
        }
        else {
            releaseDate = "No RELEASE DATE found.";
        }

        std::string description;
        if (item.contains("overview")) {
            description = item["overview"];
        }
        else {
            description = "No DESCRIPTION found.";
        }

        std::string mediaType;
        if (item.contains("media_type")) {
            mediaType = item["media_type"];
        }
        else {
            mediaType = "No MEDIA TYPE found.";
        }

        std::cout << "[" << (i + 1) << "] "
            << title << " (" << releaseDate << ") "
            << "(" << mediaType << ") "
            << "DESCRIPTION: " << description << std::endl;
    }

    //okay so this loop will says i = 0 (first item in an array since 0 = first position, then we look at the size of the api's result (the number of shit the api feeds back) then it adds 1 to that so it starts printing out "[1] name release date description"
    // 
    // to get said "name" "descritpion" "type" we gotta define them, so we turning em into strings but there's instances where "title" and "name" mean the same shit just happens to depend if its a show or a movie soooooo we gotta do this THEEEE LONGGGGGGGGG WAY ( i could've just done "?" instead of all this shit but i kinda like doing it this way for now bc it helps me read the code back better, code is self explanatory even for a retard like me and then the print out fuction boom bam slam it works idk
};
