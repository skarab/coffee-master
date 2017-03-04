function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6451\" class=\"headerLeftMenuInActive\"><a id=\"aID6451\" href=\"#\" OnMouseOver=\"link('_dir','list_view0',this)\" class=\"leftMenuLinkHeadInActive\">list_view</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1025\" class=\"leftMenuInActive\"><a id=\"aID1025\" href=\"#\" OnMouseOver=\"link('_class','ListView45101',this)\" class=\"leftMenuLinkInActive\">ListView</a></div>\n");
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
