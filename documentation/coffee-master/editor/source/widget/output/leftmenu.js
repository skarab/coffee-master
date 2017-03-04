function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6491\" class=\"headerLeftMenuInActive\"><a id=\"aID6491\" href=\"#\" OnMouseOver=\"link('_dir','output0',this)\" class=\"leftMenuLinkHeadInActive\">output</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1102\" class=\"leftMenuInActive\"><a id=\"aID1102\" href=\"#\" OnMouseOver=\"link('_class','Output22483',this)\" class=\"leftMenuLinkInActive\">Output</a></div>\n");
document.write("<div id=\"divID1103\" class=\"leftMenuInActive\"><a id=\"aID1103\" href=\"#\" OnMouseOver=\"link('_class','OutputBar22483',this)\" class=\"leftMenuLinkInActive\">OutputBar</a></div>\n");
document.write("<div id=\"divID6166\" class=\"leftMenuInActive\"><a id=\"aID6166\" href=\"#\" OnMouseOver=\"link('_class','Window0',this)\" class=\"leftMenuLinkInActive\">Window</a></div>\n");
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
