import QtQuick 2.0

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
    property string chartCaption: "График по "
    property var seriesArray

    ChartView {
        id : chartview
        antialiasing: true
        title: chartWin.chartCaption
        legend.alignment : Qt.AlignBottom

        anchors.fill: parent
    }

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

        var data = _controller.trends(selectPanel.getChosenIDs());
        var names = selectPanel.getChosenNames();
        names.sort();

        // fill chart view
        seriesArray = [];

        var maxY = 0;
        var minY = Number.MAX_VALUE;
        for (var key in data)
        {
            var points = data[key];

            for (var j in points)
            {
                var point = points[j];
                if (point.y < minY)
                    minY = point.y;
                if (point.y > maxY)
                    maxY = point.y;
            }
        }
        minY -= 0.01;
        maxY += 0.01;

        var i = 0;
        for (var key in data)
        {
            var points = data[key];
            var series = chartview.createSeries(ChartView.SeriesTypeLine, names[i]);
            series.color = Tools.getColor(i);
//            console.info(series.color);
            series.axisX.min = points[0].x;
            series.axisX.max = points[1].x;
//            series.axisX.tickCount = points[1].x - points[0].x + 1;
            series.axisX.labelFormat = "%d";
            series.axisX.tickCount = series.axisX.max - series.axisX.min + 1;
            series.axisY.labelFormat = "%0.2f";
            series.axisY.min = minY;
            series.axisY.max = maxY;
            series.axisY.titleText = "Средняя успеваемость";

            for (var j = 0; j < points.length; j++)
            {
                series.append(points[j].x, points[j].y);
            }
            seriesArray.push(series);
            i++;
        }
    }
}
