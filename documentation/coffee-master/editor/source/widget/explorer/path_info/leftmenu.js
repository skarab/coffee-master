function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6486\" class=\"headerLeftMenuInActive\"><a id=\"aID6486\" href=\"#\" OnMouseOver=\"link('_dir','path_info0',this)\" class=\"leftMenuLinkHeadInActive\">path_info</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1096\" class=\"leftMenuInActive\"><a id=\"aID1096\" href=\"#\" OnMouseOver=\"link('_class','PathInfo22483',this)\" class=\"leftMenuLinkInActive\">PathInfo</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6260\" class=\"leftMenuInActive\"><a id=\"aID6260\" href=\"#\" OnMouseOver=\"link('_member','PATH_FLAG1629766333',this)\" class=\"leftMenuLinkInActive\">PATH_FLAG</a></div>\n");
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
