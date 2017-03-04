function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6458\" class=\"headerLeftMenuInActive\"><a id=\"aID6458\" href=\"#\" OnMouseOver=\"link('_dir','tool_tip0',this)\" class=\"leftMenuLinkHeadInActive\">tool_tip</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1033\" class=\"leftMenuInActive\"><a id=\"aID1033\" href=\"#\" OnMouseOver=\"link('_class','ToolTip45101',this)\" class=\"leftMenuLinkInActive\">ToolTip</a></div>\n");
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
