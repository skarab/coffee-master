function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6488\" class=\"headerLeftMenuInActive\"><a id=\"aID6488\" href=\"#\" OnMouseOver=\"link('_dir','gizmo_controller0',this)\" class=\"leftMenuLinkHeadInActive\">gizmo_controller</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1098\" class=\"leftMenuInActive\"><a id=\"aID1098\" href=\"#\" OnMouseOver=\"link('_class','GizmoController22483',this)\" class=\"leftMenuLinkInActive\">GizmoController</a></div>\n");
document.write("<div id=\"divID6198\" class=\"leftMenuInActive\"><a id=\"aID6198\" href=\"#\" OnMouseOver=\"link('_class','Window0',this)\" class=\"leftMenuLinkInActive\">Window</a></div>\n");
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
