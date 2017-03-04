function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6460\" class=\"headerLeftMenuInActive\"><a id=\"aID6460\" href=\"#\" OnMouseOver=\"link('_dir','view_control0',this)\" class=\"leftMenuLinkHeadInActive\">view_control</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1036\" class=\"leftMenuInActive\"><a id=\"aID1036\" href=\"#\" OnMouseOver=\"link('_class','ViewContainer45101',this)\" class=\"leftMenuLinkInActive\">ViewContainer</a></div>\n");
document.write("<div id=\"divID1037\" class=\"leftMenuInActive\"><a id=\"aID1037\" href=\"#\" OnMouseOver=\"link('_class','ViewControl45101',this)\" class=\"leftMenuLinkInActive\">ViewControl</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6252\" class=\"leftMenuInActive\"><a id=\"aID6252\" href=\"#\" OnMouseOver=\"link('_member','VIEW_CONTROL_STYLE1141535755',this)\" class=\"leftMenuLinkInActive\">VIEW_CONTROL_STYLE</a></div>\n");
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
