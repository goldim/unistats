import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

Item {
    id : it

    property var model
    property var outputPanel
    property var clearPanel
    property variant tmpM: ListModel{}

    signal filterChanged(string text)
    signal choseItem(int id)
    signal showAll
    signal clearAll
    signal moveAll
    signal clearAllVisible

    onChoseItem:  {
        outputPanel.clearAll();
        clearPanel.clearAll();
        var values = _controller.loadSpecialties(model.get(id).id);

        for (var key in values)
        {
            outputPanel.model.append({id : key, name : values[key]});
        }
    }

    onFilterChanged: {
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

    onModelChanged: {
        _controller.setDomain("Faculty");
        model.loadItems();
        _controller.setDomain("Specialty");
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

            TableViewColumn {
                role: "name"
                title: "Факультеты"
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
