function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6493\" class=\"headerLeftMenuInActive\"><a id=\"aID6493\" href=\"#\" OnMouseOver=\"link('_dir','project_browser0',this)\" class=\"leftMenuLinkHeadInActive\">project_browser</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1105\" class=\"leftMenuInActive\"><a id=\"aID1105\" href=\"#\" OnMouseOver=\"link('_class','ProjectBrowser22483',this)\" class=\"leftMenuLinkInActive\">ProjectBrowser</a></div>\n");
document.write("<div id=\"divID6179\" class=\"leftMenuInActive\"><a id=\"aID6179\" href=\"#\" OnMouseOver=\"link('_class','Window0',this)\" class=\"leftMenuLinkInActive\">Window</a></div>\n");
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
