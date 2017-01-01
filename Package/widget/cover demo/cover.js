//该代码部分来自Music Player Support by RangerCD
//“是萝莉控真是太好了！” ろりこんでよかった～

var DATA_URL = "http://nvg-data/";
var ID_ODATASOURCE = "1C0C1731-D190-49F3-B34D-4A69EFD3C249";
var ID_DATA_CAD = "F3594F55-E57C-4988-BE3C-2DD4BD02C9A4";
var ID_CAD_TITLE = 2;
var ID_CAD_COVER = 8;

var UPDATE_INTERVAL = 1000; // 1s

var title = "";

function updateItem(sid, did, vid)
{
    $.ajax({
        type: "get",
        dataType: "json",
        url: DATA_URL + sid + "/" + did + "/" + vid + "/query",
        success: function (ret) {
            if (ret.data.value != " ")
                    document.getElementById("cover").src = ret.data.value + "?time=" + new Date().getTime();
                else
                    document.getElementById("cover").src = "unknown.png";
        }
    });
}

function refreshValues()
{
    updateItem(ID_ODATASOURCE, ID_DATA_CAD, ID_CAD_COVER);
}

$(function () {
    refreshValues();
    setInterval("refreshValues()", UPDATE_INTERVAL);
});
