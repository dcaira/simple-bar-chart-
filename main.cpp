#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

// Axis class: can be horizontal or vertical
class Axis {
public:
    enum class Orientation { Horizontal, Vertical };
    Axis(const std::string& label, int length, Orientation orient)
        : label_(label), length_(length), orient_(orient) {}

    void draw(std::ostream& os) const {
        if (orient_ == Orientation::Horizontal) {
            os << "   ";
            for (int i = 0; i < length_; ++i)
                os << '-';
            os << ">\n";
            os << "   " << label_ << "\n";
        } else {
            for (int i = length_; i > 0; --i)
                os << " |\n";
            os << " v\n";
            os << " " << label_ << "\n";
        }
    }

    int length() const { return length_; }
    const std::string& label() const { return label_; }
    Orientation orientation() const { return orient_; }
private:
    std::string label_;
    int length_;
    Orientation orient_;
};

// Rectangle primitive for a bar
class Rectangle {
public:
    Rectangle(int width, int height, char fill = '#')
        : width_(width), height_(height), fill_(fill) {}

    // Draws the rectangle at a given row in the bar (row 0 is the top)
    // Returns true if the rectangle occupies this row, false otherwise
    bool drawRow(int row, std::ostream& os) const {
        if (row < (height_)) {
            for (int i = 0; i < width_; ++i)
                os << fill_;
            return true;
        } else {
            for (int i = 0; i < width_; ++i)
                os << ' ';
            return false;
        }
    }

    int width() const { return width_; }
    int height() const { return height_; }
private:
    int width_;
    int height_;
    char fill_;
};

// BarChart class (vertical by default)
class BarChart {
public:
    BarChart(const Axis& h, const Axis& v)
        : hAxis(h), vAxis(v) {}

    void setData(const std::vector<std::pair<std::string, int>>& data) {
        bars_ = data;
    }

    void render(std::ostream& os) const {
        int maxVal = 0;
        for (const auto& [_, val] : bars_)
            maxVal = std::max(maxVal, val);

        const int chartHeight = vAxis.length(); // Number of rows for bars
        const int barWidth = 4;
        const int spaceBetween = 2;

        // Build rectangles for each bar, normalized to max chart height
        std::vector<Rectangle> barRects;
        for (const auto& [_, val] : bars_) {
            int height = (maxVal == 0) ? 0 : static_cast<int>(static_cast<double>(val) / maxVal * chartHeight + 0.5);
            barRects.emplace_back(barWidth, height, '#');
        }

        // Draw vertical axis label at the left
        os << std::setw(6) << vAxis.label() << "\n";

        // Draw the chart row by row (top to bottom)
        for (int row = 0; row < chartHeight; ++row) {
            int chartRow = chartHeight - row - 1; // start from the top
            os << std::setw(4) << ((maxVal * (chartRow + 1)) / chartHeight) << " | ";
            for (size_t i = 0; i < barRects.size(); ++i) {
                barRects[i].drawRow(chartRow, os);
                if (i < barRects.size() - 1)
                    os << std::string(spaceBetween, ' ');
            }
            os << "\n";
        }

        // Draw x axis
        os << "     +";
        for (size_t i = 0; i < barRects.size(); ++i) {
            for (int j = 0; j < barWidth; ++j) os << '-';
            if (i < barRects.size() - 1)
                os << std::string(spaceBetween, '-');
        }
        os << ">\n";

        // Draw bar labels
        os << "       ";  // To align axis labels with bars
        for (size_t i = 0; i < bars_.size(); ++i) {
            std::string label = bars_[i].first;
            int pad = barWidth + (i < barRects.size() - 1 ? spaceBetween : 0);
            int l = static_cast<int>(label.length());
            int leftPad = (barWidth - l) / 2;
            int rightPad = barWidth - l - leftPad;
            os << std::string(leftPad, ' ');
            os << label.substr(0, barWidth); // truncate if too long
            os << std::string(rightPad, ' ');
            if (i < barRects.size() - 1)
                os << std::string(spaceBetween, ' ');
        }
        os << "\n";
        os << "        ";
        os << hAxis.label() << "\n";
    }

private:
    Axis hAxis;
    Axis vAxis;
    std::vector<std::pair<std::string, int>> bars_;
};

int main() {
    // Example usage: vertical bar chart
    Axis hAxis("Category", 0, Axis::Orientation::Horizontal);
    Axis vAxis("Value", 10, Axis::Orientation::Vertical); // 10 rows for bars

    BarChart chart(hAxis, vAxis);
    chart.setData({
        {"App", 25},
        {"Ban", 35},
        {"Che", 15},
        {"Dat", 30}
    });

    chart.render(std::cout);

    return 0;
}
