function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6448\" class=\"headerLeftMenuInActive\"><a id=\"aID6448\" href=\"#\" OnMouseOver=\"link('_dir','group0',this)\" class=\"leftMenuLinkHeadInActive\">group</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1022\" class=\"leftMenuInActive\"><a id=\"aID1022\" href=\"#\" OnMouseOver=\"link('_class','Group45101',this)\" class=\"leftMenuLinkInActive\">Group</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6243\" class=\"leftMenuInActive\"><a id=\"aID6243\" href=\"#\" OnMouseOver=\"link('_member','GROUP_STYLE1141535755',this)\" class=\"leftMenuLinkInActive\">GROUP_STYLE</a></div>\n");
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
