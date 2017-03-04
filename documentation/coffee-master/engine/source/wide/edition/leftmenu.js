function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6419\" class=\"headerLeftMenuInActive\"><a id=\"aID6419\" href=\"#\" OnMouseOver=\"link('_dir','edition0',this)\" class=\"leftMenuLinkHeadInActive\">edition</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6420\" class=\"leftMenuInActive\"><a id=\"aID6420\" href=\"#\" OnMouseOver=\"link('_dir','gizmo/gizmo0',this)\" class=\"leftMenuLinkInActive\">gizmo</a></div>\n");
document.write("<div id=\"divID6421\" class=\"leftMenuInActive\"><a id=\"aID6421\" href=\"#\" OnMouseOver=\"link('_dir','plugin/plugin0',this)\" class=\"leftMenuLinkInActive\">plugin</a></div>\n");
document.write("<div id=\"divID6422\" class=\"leftMenuInActive\"><a id=\"aID6422\" href=\"#\" OnMouseOver=\"link('_dir','selection/selection0',this)\" class=\"leftMenuLinkInActive\">selection</a></div>\n");
document.write("<div id=\"divID6423\" class=\"leftMenuInActive\"><a id=\"aID6423\" href=\"#\" OnMouseOver=\"link('_dir','undo/undo0',this)\" class=\"leftMenuLinkInActive\">undo</a></div>\n");
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
