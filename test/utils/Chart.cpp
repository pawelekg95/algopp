#include "test/utils/Chart.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include <memory>

namespace test {

void Chart::show()
{
	(void)m_points;
    auto series = std::unique_ptr<QT_CHARTS_NAMESPACE::QLineSeries>();
    //	for (const auto& point : m_points)
    //	{
    //		series->append(point.x, point.y);
    //	}
    //    auto chart = std::unique_ptr<QT_CHARTS_NAMESPACE::QChart>();
    //    chart->legend()->hide();
    //    chart->addSeries(series);
    //    chart->createDefaultAxes();
    //    chart->setTitle("Simple line chart example");
    //    QChartView *chartView = new QChartView(chart);
    //    chartView->setRenderHint(QPainter::Antialiasing);
    //    QMainWindow window;
    //    window.setCentralWidget(chartView);
    //    window.resize(400, 300);
    //    window.show();
}

} // namespace test
