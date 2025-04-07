#define CROW_MAIN
#include "pch.hpp"
#include "fetchandFormat.h"

int main() {
    crow::SimpleApp app;
    CROW_ROUTE(app, "/search")
        ([](const crow::request& req) {
        const char* q = req.url_params.get("q");

        if (!q) {
            return crow::response(400, "Missing query");
        }

        std::string query = q;
        std::string html = fetchAndFormatMediaResults(query);

        return crow::response(html);
            });

    CROW_ROUTE(app, "/")
        ([] {
        return crow::response(
            "<html>"
            "<head>"
            "<title>Tracky</title>"
            "<style>"
            "body { font-family: sans-serif; max-width: 600px; margin: 40px auto; padding: 20px; background-color: #f9f9f9; }"
            "h1 { text-align: center; color: #333; }"
            "form { display: flex; gap: 10px; margin-bottom: 30px; justify-content: center; }"
            "input[type='text'] { flex: 1; padding: 10px; font-size: 16px; }"
            "button { padding: 10px 20px; font-size: 16px; cursor: pointer; background-color: #333; color: white; border: none; }"
            "</style>"
            "</head>"
            "<body>"
            "<h1>Tracky</h1>"
            "<form action=\"/search\" method=\"get\">"
            "<input type=\"text\" name=\"q\" placeholder=\"Search movies, shows, anime...\">"
            "<button type=\"submit\">Search</button>"
            "</form>"
            "</body>"
            "</html>"
        );
            });




    app.port(8080).multithreaded().run();
    return 0;                              
}




//int main() {
//mediaPrint();
//return 0;
//}