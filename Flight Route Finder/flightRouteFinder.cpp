#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <climits>

#include <httplib.h>
#include <nlohmann/json.hpp>

struct Flight
{
    double price;
    std::string departure;
    std::string arrival;

    Flight(const std::string &d, const std::string &a, double p) : departure(d), arrival(a), price(p) {}
};

struct ArrivalCityAndPrice
{
    double price;
    std::string end;

    ArrivalCityAndPrice(const std::string &s, double p) : end(s), price(p) {}
};

struct Route
{
    std::vector<std::string> cities;
    double totalPrice;

    Route(const std::vector<std::string> &c, double t) : cities(c), totalPrice(t) {}
};

void dfs(const std::unordered_map<std::string, std::list<ArrivalCityAndPrice>> &connections,
         std::unordered_map<std::string, bool> &isVisited, std::string start, std::string finish,
         std::vector<Route> &routes, std::vector<std::string> &path, double currCost, int maxFlights)
{
    isVisited[start] = true;
    path.push_back(start);

    if ((start == finish) && (path.size() <= maxFlights + 1))
    {
        routes.push_back(Route(path, currCost));
    }
    else
    {
        auto it = connections.find(start);
        if (it != connections.end())
        {
            for (const auto &node : it->second)
            {
                if (!isVisited[node.end])
                {
                    dfs(connections, isVisited, node.end, finish, routes, path, currCost + node.price, maxFlights);
                }
            }
        }
    }

    path.pop_back();
    isVisited[start] = false;
}

std::vector<Route> findAllPossibleRoutes(const std::vector<Flight> &flights, const std::string &start,
                                         const std::string &finish, int maxFlights = INT_MAX)
{
    std::unordered_map<std::string, std::list<ArrivalCityAndPrice>> connections;
    std::unordered_map<std::string, bool> isVisited;
    std::vector<std::string> path;
    std::vector<Route> routes;

    for (const auto &flight : flights)
    {
        ArrivalCityAndPrice s(flight.arrival, flight.price);
        connections[flight.departure].push_back(s);
        isVisited[flight.departure] = false;
    }

    double currCost = 0;
    dfs(connections, isVisited, start, finish, routes, path, currCost, maxFlights);

    std::sort(routes.begin(), routes.end(), [](const Route &one, const Route &two)
              { return one.totalPrice < two.totalPrice; });

    return routes;
}

void printRoutes(const std::vector<Route> &routes)
{
    if (routes.empty())
    {
        std::cout << "No routes\n";
    }
    else
    {
        for (const auto &route : routes)
        {
            for (size_t i = 0; i < route.cities.size(); ++i)
            {
                std::cout << route.cities[i];
                if (i < route.cities.size() - 1)
                    std::cout << " --> ";
            }
            std::cout << " || Cost: " << route.totalPrice << std::endl;
        }
    }
}

void subtask2(const httplib::Request &req, httplib::Response &res, const std::vector<Flight> &flights)
{
    try
    {
        auto json_data = nlohmann::json::parse(req.body);
        std::string origin = json_data["origin"];
        std::string destination = json_data["destination"];
        int maxFlights = json_data.contains("maxFlights") ? json_data["maxFlights"] : INT_MAX;

        std::vector<Route> routes = findAllPossibleRoutes(flights, origin, destination, maxFlights);

        nlohmann::json response_json;
        if (routes.empty())
        {
            response_json["message"] = "No routes";
        }
        else
        {
            for (const auto &route : routes)
            {
                nlohmann::json route_json;
                route_json["route"] = route.cities;
                route_json["price"] = route.totalPrice;
                response_json.push_back(route_json);
            }
        }
        res.set_content(response_json.dump(), "application/json");
    }
    catch (const std::exception &e)
    {
        res.status = 400;
        res.set_content("{\"error\": \"Invalid request\"}", "application/json");
    }
}

int main()
{
    std::vector<Flight> flights = {
        {"SOF", "LON", 10},
        {"LON", "MLE", 20},
        {"SOF", "MLE", 70},
        {"SOF", "IST", 10},
        {"IST", "CMB", 50},
        {"CMB", "MLE", 40}};

    std::string start = "SOF";
    std::string finish = "MLE";

    std::vector<Route> routes = findAllPossibleRoutes(flights, start, finish, 2);

    printRoutes(routes);

    httplib::Server svr;

    svr.Post("/find-routes", [&flights](const httplib::Request &req, httplib::Response &res)
             { subtask2(req, res, flights); });

    svr.listen("localhost", 8080);

    return 0;
}
