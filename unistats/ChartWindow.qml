import QtQuick 2.0
import QtQuick.Window 2.2
import QtCharts 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

import "tools.js" as Tools


Window {
    id : chartWin
    property string chartCaption: "График по "
    property string category
    property string info
    property string mainLegend: defaultMainLegend
    property string defaultMainLegend : "Частоты успешно сдавших экзамен группы"

    function setTitle(ctgry)
    {
        chartWin.chartCaption += Tools.categoryToDative(ctgry);
    }

    width: 640
    height: 480

//    Item {
//        id : itemsInfo
//        anchors {
//            top : parent.top
//            bottom : chartSwitch.top
//            left: parent.left
//            right: parent.right
//        }
//        Label {
//            text: "Параметры:"
//        }
//    }

    GroupBox {
        id : chartSwitch
        title: "Вид графика:"

        anchors {
            top : parent.top
            bottom : chartSquare.top
            left: parent.left
            right: parent.right
        }

        RowLayout {
            ExclusiveGroup {
                id: tabPositionGroup

                onCurrentChanged: {
                    ogive.visible = barChart.visible = cumulate.visible = polygon.visible = false;

                    switch (current.text){
                    case "Гистограмма":
                        barChart.visible = true;
                        break;
                    case "Полигон":
                        polygon.visible = true;
                        break;
                    case "Кумулята":
                        cumulate.visible = true;
                        break;
                    case "Огива":
                        ogive.visible = true;
                        break;
                    }
                }
            }
            RadioButton {
                text: "Гистограмма"
                checked: true
                exclusiveGroup: tabPositionGroup
            }
            RadioButton {
                text: "Полигон"
                exclusiveGroup: tabPositionGroup
            }
            RadioButton {
                text: "Кумулята"
                exclusiveGroup: tabPositionGroup
            }
            RadioButton {
                text: "Огива"
                exclusiveGroup: tabPositionGroup
            }
        }
    }

    Item {
        id : chartSquare
        anchors {
            top : chartSwitch.bottom
            bottom : parent.bottom
            left: parent.left
            right: parent.right
        }

        MainLineChart{
            id : ogive
            anchors.fill : parent
            visible: false
            mainLegend: chartWin.mainLegend

            function setData(categories, values){
                var accValues = [];

                var acc = 0;
                for (var key in values)
                {
                    acc = acc + parseInt(values[key]);
                    accValues.push(acc);
                }

                minX = Math.min.apply(null, accValues);
                maxX = Math.max.apply(null, accValues);
                maxY = Math.max.apply(null, categories);

                ogive.append(accValues, categories);
            }
        }

        MainLineChart{
            id : cumulate
            anchors.fill : parent
            visible: false
            mainLegend: chartWin.mainLegend

            function setData(categories, values){
                var accValues = [];

                var acc = 0;
                for (var key in values)
                {
                    acc = acc + parseInt(values[key]);
                    accValues.push(acc);
                }

                minX = Math.min.apply(null, categories);
                maxX = Math.max.apply(null, categories);
                maxY = Math.max.apply(null, accValues);

                cumulate.append(categories, accValues);
            }
        }

        MainLineChart{
            id : polygon
            anchors.fill : parent
            visible: false
            mainLegend: chartWin.mainLegend

            function setData(categories, values){
                polygon.minX = Math.min.apply(null, categories);
                polygon.maxX = Math.max.apply(null, categories);
                polygon.maxY = Math.max.apply(null, values);
                polygon.append(categories, values);
            }
        }

        MainChartView {
            id : barChart
            anchors.fill : parent
            title: chartWin.chartCaption
            visible: true            

            function setData(categories, values){
                xCat.categories = categories;
                chartSeries.append(chartWin.mainLegend, values);
                var max = Math.max.apply(null, values);
                yCat.max = Math.max(max + 0.1);
            }

            BarSeries {
                id: chartSeries
                name: chartWin.mainLegend
                axisX: BarCategoryAxis {
                   id: xCat
                }

                axisY: ValueAxis{
                   id: yCat
                   min: 0
                   max: 10
                }
            }
        }
    }

    function loadItems(){
        var IDs = selectPanel.getChosenIDs();
        return _controller.getRangeChart(IDs);
    }

    // располагаем главное окно по центру
    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);

        var res = chartWin.loadItems();
        barChart.setData(res["categories"], res["values"]);
        ogive.setData(res["categories"], res["values"]);
        cumulate.setData(res["categories"], res["values"]);
        polygon.setData(res["categories"], res["values"]);
    }
}
