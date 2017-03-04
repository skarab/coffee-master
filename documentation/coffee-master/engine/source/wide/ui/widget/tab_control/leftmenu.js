function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6455\" class=\"headerLeftMenuInActive\"><a id=\"aID6455\" href=\"#\" OnMouseOver=\"link('_dir','tab_control0',this)\" class=\"leftMenuLinkHeadInActive\">tab_control</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1030\" class=\"leftMenuInActive\"><a id=\"aID1030\" href=\"#\" OnMouseOver=\"link('_class','TabControl45101',this)\" class=\"leftMenuLinkInActive\">TabControl</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6249\" class=\"leftMenuInActive\"><a id=\"aID6249\" href=\"#\" OnMouseOver=\"link('_member','TAB_CONTROL_EVENT1141535755',this)\" class=\"leftMenuLinkInActive\">TAB_CONTROL_EVENT</a></div>\n");
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
