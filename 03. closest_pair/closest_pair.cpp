#include "closest_pair.h"

#define USING_OPTIMAL_WAY false

#include <stdexcept>
#include "algorithm"

using namespace std;

bool compare_by_x(const Point &left, const Point &right) {
    return left.x < right.x;
}

bool compare_by_y(const Point &left, const Point &right) {
    return left.y < right.y;
}

double pair_distance(pair<Point, Point> current_pair) {
    return current_pair.first.distance(current_pair.second);
}

pair<Point, Point> closest_pair_between(const vector<Point> &PLeft, const vector<Point> &PRight, pair<Point, Point> most_closest_point) {
    double d = pair_distance(most_closest_point);
    double Xm = (PLeft[PLeft.size() - 1].x + PRight[0].x) / 2;
    vector<Point> PStripe;
    for (Point point: PLeft) {
        if (abs(point.x - Xm) < d) {
            PStripe.push_back(point);
        }
    }

    for (Point point: PRight) {
        if (abs(point.x - Xm) < d) {
            PStripe.push_back(point);
        }
    }

    if (PStripe.size() < 2){
        return most_closest_point;
    }

    sort(PStripe.begin(), PStripe.end(), compare_by_y);

    Point min_first_point = PStripe[0];
    Point min_second_point = PStripe[1];
    double min_distance = min_first_point.distance(min_second_point);

    for (int first_index = 0; first_index < PStripe.size() - 1; first_index++) {
        for (int second_index = first_index + 1; second_index < PStripe.size(); second_index++) {
            if (PStripe[second_index].y - PStripe[first_index].y >= d) {
                break;
            }

            double distance = PStripe[first_index].distance(PStripe[second_index]);
            if (distance < min_distance) {
                min_first_point = PStripe[first_index];
                min_second_point = PStripe[second_index];
                min_distance = distance;
            }
        }
    }
    auto result = std::make_pair(min_first_point, min_second_point);
    return result;
}

pair<Point, Point> closest_pair(const vector<Point> &points) {

    if (points.size() < 2) {
        throw invalid_argument("Not enough points");
    }

    if (points.size() <= 3 or USING_OPTIMAL_WAY == false) {
        Point min_first_point = points[0];
        Point min_second_point = points[1];
        double min_distance = min_first_point.distance(min_second_point);

        for (Point first_point: points) {
            for (Point second_point: points) {
                if (first_point != second_point) {
                    double distance = first_point.distance(second_point);
                    if (distance < min_distance) {
                        min_first_point = first_point;
                        min_second_point = second_point;
                        min_distance = distance;
                    }
                }
            }
        }
        auto result = std::make_pair(min_first_point, min_second_point);
        return result;
    }

    vector<Point> new_points = points;
    sort(new_points.begin(), new_points.end(), compare_by_x);

    vector<Point> PLeft(new_points.begin(), new_points.begin() + new_points.size() / 2);
    vector<Point> PRight(new_points.begin() + new_points.size() / 2, new_points.end());
    auto pl = closest_pair(PLeft);
    auto pr = closest_pair(PRight);

    auto most_closest_pair = pl;
    if (pair_distance(pr) < pair_distance(pl)){
        most_closest_pair = pr;
    }

    double d = min(pair_distance(pl), pair_distance(pr));
    auto pb = closest_pair_between(PLeft, PRight, most_closest_pair);


    if (pair_distance(pb) < d) {
        return pb;
    }else if (pair_distance(pl) < pair_distance(pr)) {
        return pl;
    } else {
        return pr;
    }


}

