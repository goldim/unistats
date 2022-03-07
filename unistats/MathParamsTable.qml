import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

Item{
    id: mathParamsPanel

    Button {
        id: getStatsBtn
        text: "Статистика"
        anchors {
            left: parent.left
            right: parent.right
        }

        onClicked: {
           var IDs = selectPanel.getChosenIDs();
            if (IDs.length === 0)
            {
                messageDialog.open();
                return;
            }


           var names = selectPanel.getChosenNames();
           var stats = _controller.getStats(IDs);
           if (names.length === 0)
           {
               it.resetStats();
               return;
           }

           it.setStats(stats);
           var sampleStr = "Выборка:<br/>";

           for (var key in names)
           {
              sampleStr += names[key] + "<br/>";
           }

           resultCon.addMsg(stats["conclusion"]);
           resultCon.addMsg(sampleStr);
        }
    }

ScrollView{
    id: it

    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
    verticalScrollBarPolicy: Qt.ScrollBarAlwaysOn
    frameVisible: true

    anchors {
        top: getStatsBtn.bottom
        bottom: parent.bottom
        left: parent.left
        right: parent.right
    }

    function setStats(stats){
        meanValue.setValue(stats["mean"]);
        varianceValue.setValue(stats["variance"]);
        acValue.setValue(stats["skewness"]);
        ekValue.setValue(stats["kurtosis"]);
        nValue.setValue(stats["n"]);
        varFactorValue.setValue(stats["varFactor"]);
        regressionValue.setValue(stats["regression"]);
        autocorrelationValue.setValue(stats["autocorrelation"]);
    }

    function resetStats()
    {
        meanValue.setValue(0);
        varianceValue.setValue(0);
        acValue.setValue(0);
        ekValue.setValue(0);
        nValue.setValue(0);
        varFactorValue.setValue(0);
        regressionValue.setValue(0);
        autocorrelationValue.setValue(0);
    }

    GridLayout {
        columns: 2

        MathSign{
            id : nSign
            title: "N"
            tooltip: "Количество элементов"
        }

        MathValue {
           id : nValue
        }

        MathSign{
            id : meanSign
            title: "M"
            tooltip: "Мат. ожидание"
        }

        MathValue {
            id : meanValue            
        }

        MathSign {
            id : varianceSign
            title: "D"
            tooltip: "Дисперсия"
        }

        MathValue {
            id : varianceValue            
        }

        MathSign {
            id : acSign
            title: "Ac"
            tooltip: "Ассиметрия"
        }

        MathValue {
            id : acValue            
        }

        MathSign {
            id : ekSign
            title : "Ek"
            tooltip: "Эксцесс"
        }

        MathValue {
            id : ekValue         
        }

        MathSign {
            id : varFactorSign
            title : "Cv"
            tooltip: "Коэф. вариации"
        }

        MathValue {
            id : varFactorValue
        }

        MathSign {
            id : regressionSign
            title : "R"
            tooltip: "Коэф. корреляции"
        }

        MathValue {
            id : regressionValue
        }

        MathSign {
            id : autocorrelationSign
            title : "AutoR"
            tooltip: "Коэф. корреляции"
        }

        MathValue {
            id : autocorrelationValue
        }
    }
}

}
