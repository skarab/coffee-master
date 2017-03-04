function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6457\" class=\"headerLeftMenuInActive\"><a id=\"aID6457\" href=\"#\" OnMouseOver=\"link('_dir','tool_bar0',this)\" class=\"leftMenuLinkHeadInActive\">tool_bar</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1032\" class=\"leftMenuInActive\"><a id=\"aID1032\" href=\"#\" OnMouseOver=\"link('_class','ToolBar45101',this)\" class=\"leftMenuLinkInActive\">ToolBar</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6251\" class=\"leftMenuInActive\"><a id=\"aID6251\" href=\"#\" OnMouseOver=\"link('_member','TOOL_BAR_STYLE1141535755',this)\" class=\"leftMenuLinkInActive\">TOOL_BAR_STYLE</a></div>\n");
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
