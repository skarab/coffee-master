function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6420\" class=\"headerLeftMenuInActive\"><a id=\"aID6420\" href=\"#\" OnMouseOver=\"link('_dir','gizmo0',this)\" class=\"leftMenuLinkHeadInActive\">gizmo</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID940\" class=\"leftMenuInActive\"><a id=\"aID940\" href=\"#\" OnMouseOver=\"link('_class','Gizmo39455',this)\" class=\"leftMenuLinkInActive\">Gizmo</a></div>\n");
document.write("<div id=\"divID941\" class=\"leftMenuInActive\"><a id=\"aID941\" href=\"#\" OnMouseOver=\"link('_class','GizmoController39455',this)\" class=\"leftMenuLinkInActive\">GizmoController</a></div>\n");
document.write("<div id=\"divID942\" class=\"leftMenuInActive\"><a id=\"aID942\" href=\"#\" OnMouseOver=\"link('_class','GizmoMesh39455',this)\" class=\"leftMenuLinkInActive\">GizmoMesh</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6231\" class=\"leftMenuInActive\"><a id=\"aID6231\" href=\"#\" OnMouseOver=\"link('_member','GIZMO_AXIS3789442812',this)\" class=\"leftMenuLinkInActive\">GIZMO_AXIS</a></div>\n");
document.write("<div id=\"divID6232\" class=\"leftMenuInActive\"><a id=\"aID6232\" href=\"#\" OnMouseOver=\"link('_member','GIZMO_MODE3789442812',this)\" class=\"leftMenuLinkInActive\">GIZMO_MODE</a></div>\n");
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
