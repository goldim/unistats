import QtQuick 2.0
import QtCharts 2.0

MainChartView {
    id: it
    property var minX: 0
    property var maxX
    property var maxY
    property string mainLegend

    function append(arr1, arr2){
        for (var i = 0; i < arr1.length; i++)
        {
            lineSeries.append(arr1[i], arr2[i]);
        }
    }

    LineSeries {
        id : lineSeries
        name : it.mainLegend

        axisX: ValueAxis{
           id: xCat
           min: minX
           max: maxX === 0 ? 10 : maxX
           labelFormat: "%d"
        }

        axisY: ValueAxis{
           id: yCat
           min: 0
           max: maxY ===0 ? 10 : maxY
           labelFormat: "%d"
        }
    }
}
