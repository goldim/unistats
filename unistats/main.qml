import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtCharts 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.1

import "models" as Models
import "tools.js" as Tools
//import "views" as Views

ApplicationWindow {
    id : mainWin    
    visible: true
    width: 640
    height: 480
    title: qsTr("Матеметический Анализатор Статистики Университета")

    // располагаем главное окнопо центру
    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }

    AboutWindow {
        id : aboutWin
    }

    MessageDialog {
        id: messageDialog
        title: "Ошибка"
        text: "Нет выбранных элементов"
    }

    menuBar : MenuBar {
       Menu {
           title: "Настройки"
           Menu {
               title: "Вид графика"
               MenuItem {
                   text: "Гистограмма"
               }
               MenuItem { text: "Ломанная" }
               MenuItem { text: "Кумулятива" }
           }
       }

       Menu {
           title: "Помощь"
           MenuItem {
               text: "О программе"
               onTriggered: aboutWin.visible = true
           }
       }
    }

    ToolBar
    {
        id : rangeFiltersBar

        anchors {
            top : parent.top
        }

        RowLayout {
            anchors.fill: parent

            Label {
                id : grTypeLbl
                text: " Катег:"
                anchors.verticalCenter: parent.verticalCenter
            }

            ComboBox {
                id: categoryBox
                anchors.verticalCenter: parent.verticalCenter
                property string category
                property string categoryText

                onCurrentIndexChanged: {
                    var item = categoryBox.model.get(currentIndex);
                    category = item.category;
                    categoryText = item.text;
                    var categoryFrom = categoryBox.model.get(currentIndex).categoryfrom;
                    _controller.setDomain(category);
//                    if (lastItem != null)
//                        selectPanel.chooseModel(currentIndex + 1, categoryFrom)
//                    else
                    selectPanel.chooseModel(currentIndex, categoryFrom)
//                    criterionBox.hide(category);
                }

//                property var lastItem: null
//                property var lastItemIndex

//                function hide(item)
//                {
//                    if (lastItem !== null)
//                    {
//                        console.info("cat NULL");
//                        categoryM.insert(lastItemIndex, lastItem);
//                    }
//                    var bNoItem = true;
//                    for (var i = 0; i < categoryM.count; i++)
//                    {
//                        var el = categoryM.get(i);
//                        if (el.category === item)
//                        {
////                            if (i === categoryBox.currentIndex)
////                            {
////                                categoryBox.currentIndex = i + 1;
////                            }

//                            lastItem = JSON.parse(JSON.stringify(el));
//                            lastItemIndex = i + 1;
//                            categoryM.remove(i);
//                            bNoItem = false;
//                            break;
//                        }
//                    }
//                    if (bNoItem)
//                        lastItem = null;
//                }

                model: categoryM//ListModel{}
            }

            Label {
                id : examOrderLbl;
                text: "Экзамен:"
                anchors.verticalCenter: parent.verticalCenter
            }

            ComboBox {
                id: examOrderBox
                anchors.verticalCenter: parent.verticalCenter

                onCurrentIndexChanged: {
                    var order = examOrder.get(currentIndex).value;
                     _controller.setOrder(order);
                }

                model: ListModel
                {
                    id: examOrder
                    ListElement { value: 0; text: "-" }
                    ListElement { value: 1; text: "1" }
                    ListElement { value: 2; text: "2" }
                    ListElement { value: 3; text: "3" }
                    ListElement { value: 4; text: "4" }
                }
            }

            Label {
                id : klassLbl;
                text: "Класс:"
                anchors.verticalCenter: parent.verticalCenter
            }

            ComboBox {
                id: klassBox
                anchors.verticalCenter: parent.verticalCenter
                textRole: "text"

                model: ListModel
                {
                    id: klassM
                    property bool bLoaded: false

                    function loadKlasses(){
                        var klasses = _controller.getGroupClasses();
                        klassM.append({value: 0, text: "-"});
                        for (var key in klasses)
                        {
                            klassM.append({value: klasses[key], text: klasses[key].toString()});
                        }
                        klassM.bLoaded = true;
                    }
                }

                onCurrentIndexChanged: {
                    if (!klassM.bLoaded)
                        klassM.loadKlasses();
                    var klass = klassM.get(currentIndex).value;
                     _controller.setGroupClass(klass);
                }
            }

            Item { Layout.fillWidth: true }
            ToolButton {
                iconSource: "images/chart.png"
                tooltip: "Построить интервальный ряд"
                onClicked: {
                    makeChart();
                }
                Layout.alignment: Qt.AlignRight
            }
        }
    }

    ToolBar
    {
        id : perfFiltersBar
        anchors {
            top : rangeFiltersBar.bottom
        }

        RowLayout {
            anchors.fill: parent

            Label {
                text: "Успеваемость по "
                anchors.verticalCenter: parent.verticalCenter
            }

            ComboBox {
                id: criterionBox
                property string criterionText
                property string criterion
                anchors.verticalCenter: parent.verticalCenter

                onCurrentIndexChanged: {
                    criterion = criterionBox.model.get(currentIndex).value;
                    criterionText = criterionBox.model.get(currentIndex).text;
                     _controller.setCriterion(criterion);
//                    categoryBox.hide(criterion);
                }

//                property var lastItem: null
//                property var lastItemIndex

//                function hide(item)
//                {
//                    if (lastItem !== null)
//                    {
//                        console.info("NULL!!");
//                        criterionM.insert(lastItemIndex, lastItem);
//                    }
//                    var bNoItem = true;
//                    for (var i = 0; i < criterionM.count; i++)
//                    {
//                        var el = criterionM.get(i);
//                        if (el.value === item)
//                        {
////                            if (i === criterionM.currentIndex)
////                            {
////                                criterionBox.currentIndex = i + 1;
////                            }

//                            lastItem = JSON.parse(JSON.stringify(el));
//                            lastItemIndex = i + 1;
//                            criterionM.remove(i);
//                            bNoItem = false;
//                            break;
//                        }
//                    }
//                    if (bNoItem)
//                        lastItem = null;
//                }

                model: criterionM//ListModel{}
            }

            Label {
                text: "раздельно"
                anchors.verticalCenter: parent.verticalCenter
            }

            CheckBox {
                id: separateMode
                checked: true
                anchors.verticalCenter: parent.verticalCenter
            }
            Item { Layout.fillWidth: true }

            ToolButton {
                iconSource: "images/anova.png"
                tooltip: "Дисперсионный анализ"
                onClicked: {
                    if (selectPanel.getChosenIDs().length === 0)
                    {
                        messageDialog.open();
                        return;
                    }

                    var res = "Фактор <b>A</b> - <i>" + Tools.categoryToNominative(criterionBox.criterion)
                            + "</i> включает:<br/>";
                    res += "Фактор <b>B</b> - <i>" + categoryBox.categoryText + "</i> включает:<br/>";
                    var names = selectPanel.getChosenNames();
                    for (var key in names)
                    {
                       res += names[key] + "<br/>";
                    }
                    res += _controller.getAnova2(selectPanel.getChosenIDs());
                    resultCon.addMsg(res);
                }
                Layout.alignment: Qt.AlignRight
            }

            ToolButton {
                iconSource: "images/trend.png"
                tooltip: "Тренды"
                onClicked: {
                    if (selectPanel.getChosenIDs().length === 0)
                    {
                        messageDialog.open();
                        return;
                    }
                    var component = Qt.createComponent("TrendWindow.qml");
                    var win = component.createObject(mainWin);
                    win.setTitle(categoryBox.category);
                    win.setXTitle(criterionBox.criterion);
                    win.show();
                }
                Layout.alignment: Qt.AlignRight
            }

            ToolButton {
                iconSource: "images/correlation.png"
                tooltip: "Матрица ковариации"
                onClicked: {
                    if (selectPanel.getChosenIDs().length === 0)
                    {
                        messageDialog.open();
                        return;
                    }

                    var component = Qt.createComponent("CorrelationWindow.qml");
                    var win = component.createObject(mainWin);
                    win.setTitle(categoryBox.category);
                    win.setXTitle(criterionBox.criterion);
                    win.show();
                }
                Layout.alignment: Qt.AlignRight
            }

            ToolButton {
                iconSource: "images/chart.png"
                tooltip: "Построить график успеваемости"
                onClicked: {
                    if (separateMode.checked)
                        makeSeparateChart();
                    else
                        makeChart();
                }
                Layout.alignment: Qt.AlignRight
            }            
        }
    }

    SplitView {
        anchors {
            top : perfFiltersBar.bottom
            bottom : parent.bottom
            left : parent.left
            right : parent.right
        }
        orientation: Qt.Vertical

        Item {
            Layout.fillHeight: true
            Layout.minimumHeight: parent.height * 0.1

            SelectPanel {
                id : selectPanel
//                width : parent.width * 0.8
                anchors {
                    left: parent.left
                    top: parent.top
                    bottom: parent.bottom
                    right: mathParamsPanel.left
                }
            }

            MathParamsTable {
                id : mathParamsPanel
                width : 120
                anchors {
                    right : parent.right
                    top: parent.top
                    bottom: parent.bottom
//                    left: selectPanel.right
                }
            }
        }

        ResultConsole {
            id : resultCon
            Layout.minimumHeight: parent.height * 0.2
        }
    }

    Models.CategoryComboBox {
        id: categoryM
    }

    ListModel {
        id: criterionM
        ListElement { value: "ExamOrder"; text: "номеру экзамена"}
        ListElement { value: "Year"; text: "годам" }
        ListElement { value: "Term"; text: "семестрам" }
        ListElement { value: "Kurs"; text: "курсам" }
        ListElement { value: "YearStart"; text: "годам набора" }
    }

    function makeSeparateChart()
    {
        if (selectPanel.getChosenIDs().length === 0)
        {
            messageDialog.open();
            return;
        }

        var component;
        var win;
        component = Qt.createComponent("MultiLineChartWindow.qml");
        win = component.createObject(mainWin);
        win.setTitle(categoryBox.category);
        win.setXTitle(criterionBox.criterion);
        win.show();
    }

    function makeChart()
    {
        if (selectPanel.getChosenIDs().length === 0)
        {
            messageDialog.open();
            return;
        }

        var component;
        var win;

        component = Qt.createComponent("ChartWindow.qml");
        win = component.createObject(mainWin);
        win.setTitle(categoryBox.category);
        win.show();
    }
}
