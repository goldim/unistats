import QtQuick 2.0
import QtQuick.Window 2.2
import QtCharts 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

import "tools.js" as Tools

Window {
    id : chartWin
    width: 960
    height: 480
    property string chartCaption: "График по "
    property var seriesArray

    ChartView {
        id : chartview
        antialiasing: true
        title: chartWin.chartCaption
        legend.alignment : Qt.AlignBottom

//        anchors.fill: parent
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
//            right : parent.horizontalCenter
//            right: parent.right
        }

        width: (parent.width / 3) * 2
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

        var data = _controller.correlation(selectPanel.getChosenIDs());
        var names = selectPanel.getChosenNames();
        names.sort();

        // fill chart view
        var chartdata = data["chartdata"];
        seriesArray = [];

        var maxY = 0;
        var minY = Number.MAX_VALUE;
        for (var i in chartdata)
        {
            var values = chartdata[i]["values"];
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

        var i = 0;
        for (var key in chartdata)
        {
            var categories = chartdata[key]["categories"];
            var values = chartdata[key]["values"];
            var series = chartview.createSeries(ChartView.SeriesTypeScatter, names[i]);
            series.color = Tools.getColor(i);
            series.axisX.min = categories[0] - 1;
            series.axisX.max = categories[categories.length - 1] + 1;
            series.axisX.tickCount = series.axisX.max - series.axisX.min + 1;
            series.axisX.labelFormat = "%d";
            series.axisY.tickCount = 11;
            series.axisY.min = parseFloat(minY) - 0.01;
            series.axisY.max = parseFloat(maxY) + 0.01;
            series.axisY.labelFormat = "%0.2f";
            series.axisY.titleText = "Средняя успеваемость";

            for (var j = 0; j < categories.length; j++)
            {
                series.append(categories[j], values[j]);
            }
            seriesArray.push(series);
            i++;
        }

        // fill table view
        var tabledata = data["tabledata"];
        var roles = tabledata["roles"];

        var nameCln = Qt.createQmlObject(
                    "import QtQuick 2.0;
                     import QtQuick.Controls 1.4;
                     TableViewColumn {role:'name';title: 'Название';width:70;movable:false}",
                                           tableview);

        tableview.addColumn(nameCln);

        var numberCln = Qt.createQmlObject(
                    "import QtQuick 2.0;
                     import QtQuick.Controls 1.4;
                     TableViewColumn {role:'No';title: '№';width:30;
                                        resizable:false;movable:false}",
                                           tableview);

        tableview.addColumn(numberCln);


        for (var i = 0; i < roles.length; i++)
        {
            var cln = Qt.createQmlObject(
                        "import QtQuick 2.0;
                         import QtQuick.Controls 1.4;
                         TableViewColumn {role:'"+roles[i]+"';title: '"+(i+1)+"';width:50}",
                                               tableview);

            tableview.addColumn(cln);
        }


        // fill model
        var factors = tabledata["factors"];

        for (var i = 0; i < roles.length; i++)
        {
            var row = new Object;
            row.name = names[i];//roles[i];
            row.No = i + 1;
            for (var factor in factors)
            {
                var el = factors[factor];
                row[factor] = el[i];
            }

            covarianceMatrix.append(row);
        }
    }

    TableView{
        id: tableview

        anchors {
            top: parent.top
            bottom: parent.bottom
//            left: parent.chartview
            right : parent.right
        }

        width: parent.width / 3
        model: covarianceMatrix
    }

    ListModel {
        id: covarianceMatrix
    }
}
