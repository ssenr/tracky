#pragma once
#include "pch.hpp"

std::string fetchAndFormatMediaResults(const std::string& query) {
    std::ifstream key_file("key.json");
    json key = json::parse(key_file);

    std::string api_key = key["TMDB_KEY"];
    std::string url = "https://api.themoviedb.org/3/search/multi?api_key=" + api_key + "&query=" + cpr::util::urlEncode(query);

    cpr::Response cprMediaResponse = cpr::Get(cpr::Url{ url });

    json data = json::parse(cprMediaResponse.text);
    json results = data["results"];

    std::string html;

    for (const json& item : results) {
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

        html += "<div>";
        html += "<h2>" + title + " (" + releaseDate + ")</h2>";
        html += "<p>" + description + "</p>";
        html += "<p>" + mediaType + "</p>";
        html += "</div>\n";
    }

    return html;
}
