function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6454\" class=\"headerLeftMenuInActive\"><a id=\"aID6454\" href=\"#\" OnMouseOver=\"link('_dir','scroll_bar0',this)\" class=\"leftMenuLinkHeadInActive\">scroll_bar</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1029\" class=\"leftMenuInActive\"><a id=\"aID1029\" href=\"#\" OnMouseOver=\"link('_class','ScrollBar45101',this)\" class=\"leftMenuLinkInActive\">ScrollBar</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6248\" class=\"leftMenuInActive\"><a id=\"aID6248\" href=\"#\" OnMouseOver=\"link('_member','SCROLL_BAR_STYLE1141535755',this)\" class=\"leftMenuLinkInActive\">SCROLL_BAR_STYLE</a></div>\n");
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
