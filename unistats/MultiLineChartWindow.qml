import QtQuick 2.0
import QtQuick.Window 2.2
import QtCharts 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

import "tools.js" as Tools

Window {
    id : chartWin
    width: 640
    height: 480
    property alias chartView: chart
    property alias mainTitle: chart.title
    property string chartCaption: "График по "
    property string xTitle
    property var seriesArray

    function setTitle(ctgry)
    {
        chartWin.chartCaption += Tools.categoryToDative(ctgry);
    }

    function setXTitle(ctgry)
    {
        var title = Tools.categoryToNominative(ctgry);
        for (var key in seriesArray)
        {
            seriesArray[key].axisX.titleText = title;
        }
    }

    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }

    ChartView {
        id : chart
        antialiasing: true
        anchors.fill : parent
        title: chartWin.chartCaption
        legend.showToolTips : true
        legend.alignment : Qt.AlignRight

        // располагаем главное окно по центру
        Component.onCompleted: {
            seriesArray = [];
            var IDs = selectPanel.getChosenIDs();
            var names = selectPanel.getChosenNames();
            var data = [];
            //получение данных
            for (var i = 0; i < IDs.length; i++)
            {
                 data.push(_controller.getTimeChart([IDs[i]]));
            }

            //нахождение экстремумов
            var max = 0;
            var min = Number.MAX_VALUE;
            var count = 0;
            for (i = 0; i < data.length; i++)
            {
                var categories = data[i]["categories"];
                if (categories.length > count)
                    count = categories.length;
                for (var j in categories)
                {
                    var tmp = parseInt(categories[j]);
                    if (min > tmp)
                        min = tmp;
                    if (max < tmp)
                        max = tmp;
                }
            }

            var maxY = 0;
            var minY = Number.MAX_VALUE;
            for (i = 0; i < data.length; i++)
            {
                var values = data[i]["values"];
                for (var j in values)
                {
                    if (values[j] < minY)
                        minY = values[j];
                    if (values[j] > maxY)
                        maxY = values[j];
                }
            }
            minY = parseFloat(minY) - 0.01;
            maxY = parseFloat(maxY) + 0.01;

            //создание и заполнение серий
            for (i = 0; i < data.length; i++)
            {
                var categories = data[i]["categories"];
                var values = data[i]["values"];
                var series = chart.createSeries(ChartView.SeriesTypeSpline, names[i]);
                series.color = Tools.getColor(i);
                series.axisX.titleText = chartWin.xTitle;

                max - min + 1 == 1

                if (max - min + 1 == 1)
                {
                    series.axisX.min = min - 1;
                    series.axisX.tickCount = 3;
                    series.axisX.labelFormat = "%d";
                    series.axisX.max = max + 1;
                }
                else
                {
                    series.axisX.min = min;
                    series.axisX.tickCount = max - min + 1;
                    series.axisX.labelFormat = "%d";
                    series.axisX.max = max;
                }

                series.axisY.min = minY;
                series.axisY.max = maxY;
                series.axisY.labelFormat = "%0.2f";
//                series.axisY.tickCount = 11;
                series.axisY.titleText = "Средняя успеваемость";

                if (categories.length === 1)
                {
                    series.append(min - 1, 0);
                }

                for (var j = 0; j < categories.length; j++)
                {
                    series.append(categories[j], values[j]);
                }

                if (categories.length === 1)
                {
                    series.append(max + 1, 0);
                }

                seriesArray.push(series);
            }

        }
    }

    function createAxis(categories) {
        // The following creates a ValueAxis object that can be then set as a x or y axis for a series
        var min = Math.min.apply(null, categories);
        var max = Math.max.apply(null, categories);
        var tickCount = categories.length;
        return Qt.createQmlObject("import QtQuick 2.0; import QtCharts 2.0; ValueAxis { tickCount: "+tickCount+"; min: "
                                      + min + "; max: " + max + "}", chart);
    }
}
