function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6482\" class=\"headerLeftMenuInActive\"><a id=\"aID6482\" href=\"#\" OnMouseOver=\"link('_dir','config_dialog0',this)\" class=\"leftMenuLinkHeadInActive\">config_dialog</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1088\" class=\"leftMenuInActive\"><a id=\"aID1088\" href=\"#\" OnMouseOver=\"link('_class','ConfigAudio22483',this)\" class=\"leftMenuLinkInActive\">ConfigAudio</a></div>\n");
document.write("<div id=\"divID1089\" class=\"leftMenuInActive\"><a id=\"aID1089\" href=\"#\" OnMouseOver=\"link('_class','ConfigDialog22483',this)\" class=\"leftMenuLinkInActive\">ConfigDialog</a></div>\n");
document.write("<div id=\"divID1090\" class=\"leftMenuInActive\"><a id=\"aID1090\" href=\"#\" OnMouseOver=\"link('_class','ConfigGeneral22483',this)\" class=\"leftMenuLinkInActive\">ConfigGeneral</a></div>\n");
document.write("<div id=\"divID1091\" class=\"leftMenuInActive\"><a id=\"aID1091\" href=\"#\" OnMouseOver=\"link('_class','ConfigGraphics22483',this)\" class=\"leftMenuLinkInActive\">ConfigGraphics</a></div>\n");
document.write("<div id=\"divID1092\" class=\"leftMenuInActive\"><a id=\"aID1092\" href=\"#\" OnMouseOver=\"link('_class','ConfigShortcuts22483',this)\" class=\"leftMenuLinkInActive\">ConfigShortcuts</a></div>\n");
document.write("<div id=\"divID6188\" class=\"leftMenuInActive\"><a id=\"aID6188\" href=\"#\" OnMouseOver=\"link('_class','Dialog0',this)\" class=\"leftMenuLinkInActive\">Dialog</a></div>\n");
document.write("<div id=\"divID6184\" class=\"leftMenuInActive\"><a id=\"aID6184\" href=\"#\" OnMouseOver=\"link('_class','Window0',this)\" class=\"leftMenuLinkInActive\">Window</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
