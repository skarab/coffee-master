function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6490\" class=\"headerLeftMenuInActive\"><a id=\"aID6490\" href=\"#\" OnMouseOver=\"link('_dir','node_editor0',this)\" class=\"leftMenuLinkHeadInActive\">node_editor</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1100\" class=\"leftMenuInActive\"><a id=\"aID1100\" href=\"#\" OnMouseOver=\"link('_class','NodeEditor22483',this)\" class=\"leftMenuLinkInActive\">NodeEditor</a></div>\n");
document.write("<div id=\"divID1101\" class=\"leftMenuInActive\"><a id=\"aID1101\" href=\"#\" OnMouseOver=\"link('_class','NodeEditorComponent22483',this)\" class=\"leftMenuLinkInActive\">NodeEditorComponent</a></div>\n");
document.write("<div id=\"divID6172\" class=\"leftMenuInActive\"><a id=\"aID6172\" href=\"#\" OnMouseOver=\"link('_class','Property0',this)\" class=\"leftMenuLinkInActive\">Property</a></div>\n");
document.write("<div id=\"divID6199\" class=\"leftMenuInActive\"><a id=\"aID6199\" href=\"#\" OnMouseOver=\"link('_class','Window0',this)\" class=\"leftMenuLinkInActive\">Window</a></div>\n");
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
