function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6447\" class=\"headerLeftMenuInActive\"><a id=\"aID6447\" href=\"#\" OnMouseOver=\"link('_dir','edit_box0',this)\" class=\"leftMenuLinkHeadInActive\">edit_box</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1021\" class=\"leftMenuInActive\"><a id=\"aID1021\" href=\"#\" OnMouseOver=\"link('_class','EditBox45101',this)\" class=\"leftMenuLinkInActive\">EditBox</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6242\" class=\"leftMenuInActive\"><a id=\"aID6242\" href=\"#\" OnMouseOver=\"link('_member','EDIT_BOX_STYLE1141535755',this)\" class=\"leftMenuLinkInActive\">EDIT_BOX_STYLE</a></div>\n");
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
