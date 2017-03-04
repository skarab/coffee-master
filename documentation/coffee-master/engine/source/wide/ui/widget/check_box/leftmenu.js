function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6444\" class=\"headerLeftMenuInActive\"><a id=\"aID6444\" href=\"#\" OnMouseOver=\"link('_dir','check_box0',this)\" class=\"leftMenuLinkHeadInActive\">check_box</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1017\" class=\"leftMenuInActive\"><a id=\"aID1017\" href=\"#\" OnMouseOver=\"link('_class','CheckBox45101',this)\" class=\"leftMenuLinkInActive\">CheckBox</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6239\" class=\"leftMenuInActive\"><a id=\"aID6239\" href=\"#\" OnMouseOver=\"link('_member','CHECK_BOX_STATE1141535755',this)\" class=\"leftMenuLinkInActive\">CHECK_BOX_STATE</a></div>\n");
document.write("<div id=\"divID6240\" class=\"leftMenuInActive\"><a id=\"aID6240\" href=\"#\" OnMouseOver=\"link('_member','CHECK_BOX_STYLE1141535755',this)\" class=\"leftMenuLinkInActive\">CHECK_BOX_STYLE</a></div>\n");
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
