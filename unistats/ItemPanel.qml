import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import "tools.js" as Tools

//TODO Копирование в столбец с включенным фильтром добавляет элемент в список видимых элементов

Item {        
        id : it
        property string viewTitle
        property variant model
        property variant tmpM: ListModel{}
        property string barElementsAlign : "right"
        property var toModel

        signal filterChanged(string text)
        signal choseItem(int id)
        signal showAll
        signal clearAll
        signal moveAll
        signal clearAllVisible

        onChoseItem:  {
            toModel.append(model.get(id));
            model.remove(id);
        }

        onMoveAll: {
            for (var i = 0; i < model.count; i++)
            {
                toModel.append(model.get(i));
            }

            it.clearAllVisible();
        }


        onClearAll: {
            clearSelection(model);
            clearSelection(tmpM);
        }

        onClearAllVisible: clearSelection(model);

        onShowAll: {            
            for (var i = 0; i < tmpM.count; i++)
            {
                model.append(tmpM.get(i));
                tmpM.remove(i);
                i = i - 1;
            }
        }

        onFilterChanged: {
           if (testTV.currentRow == -1)// перемещение элемента из одной в таблицы в другую
           {
               if (testTV.model.count != 0)
               {
                   testTV.selection.select(0);
                   testTV.currentRow = 0;
               }
           }

           for (var i = 0; i < model.count; i++)
           {
               if (!it.isEqual(model.get(i).name, text))
               {
                   tmpM.append(model.get(i));
                   model.remove(i);
                   i = i - 1;
               }
           }

           for (i = 0; i < tmpM.count; i++)
           {
               if (it.isEqual(tmpM.get(i).name, text))
               {
                   model.append(tmpM.get(i));
                   tmpM.remove(i);
                   i = i - 1;
               }
           }
        }

        ColumnLayout {
            anchors.fill: parent

            ToolBar {
                id : rowBar
                height : 20
                anchors {
                    left : parent.left
                    right : parent.right
                    top : parent.top
                    bottom : testTV.top
                }

                ToolButton {
                    anchors.right: if (it.barElementsAlign == "right") return parent.right
                    anchors.left: if (it.barElementsAlign == "left") return parent.left
                    text : (it.barElementsAlign == "left") ? "<<" : ">>"
                    onClicked: moveAll()
                }
            }

            TableView {
                id : testTV
                anchors {
                    //TODO QML Item: Binding loop detected for property "width"
                    top : rowBar.bottom
                    left : parent.left
                    right : parent.right
                    bottom : filterRow.top
                }

                sortIndicatorVisible: true
                onSortIndicatorOrderChanged: model.sortEvent(sortIndicatorOrder);
                onClicked : choseItem(row)
                Keys.onReturnPressed: {
                    //перемещение элемента из одной таблицы в другую
                    if (testTV.model.count != 0 && testTV.currentRow != -1)
                        it.choseItem(testTV.currentRow);
                }

                TableViewColumn {
                    role: "name"
                    title: it.viewTitle
                    resizable : false
                }

                model : it.model
            }

            RowLayout {
                id : filterRow
                height : 20
                anchors {
                    bottom : parent.bottom
                    left : parent.left
                    right : parent.right
                }

                Button {
                    id: filterBtn
                    iconSource: {
                        if (filterFld.text === "")
                            return "images/filter.png"
                        else
                            return "images/filled-filter.png"
                    }
                    onClicked: {
                        filterFld.text = "";
                        showAll();
                    }
                }
                TextField {
                    id : filterFld
                    placeholderText: "Введите слово"
                    anchors.left: filterBtn.right
                    anchors.right: parent.right
                    onTextChanged: {                        
                        it.filterChanged(text)
                    }
                    Keys.onReturnPressed: {
                        //перемещение элемента из одной таблицы в другую
                        if (testTV.model.count != 0 && testTV.currentRow != -1)
                            it.choseItem(testTV.currentRow);
                    }
                }
            }
        }

        // функция сравнения строк
        function isEqual(str1, str2){
            return str1.substring(0, str2.length) === str2;
        }

        //удалить все элементы модели
        function clearSelection(model){
            for (var i = 0; i < model.count; i++)
            {
                model.remove(i);
                i = i-1;
            }
        }
}
