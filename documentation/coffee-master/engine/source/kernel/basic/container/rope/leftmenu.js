function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6271\" class=\"headerLeftMenuInActive\"><a id=\"aID6271\" href=\"#\" OnMouseOver=\"link('_dir','rope0',this)\" class=\"leftMenuLinkHeadInActive\">rope</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID6175\" class=\"leftMenuInActive\"><a id=\"aID6175\" href=\"#\" OnMouseOver=\"link('_class','Container0',this)\" class=\"leftMenuLinkInActive\">Container</a></div>\n");
document.write("<div id=\"divID731\" class=\"leftMenuInActive\"><a id=\"aID731\" href=\"#\" OnMouseOver=\"link('_class','Rope39222',this)\" class=\"leftMenuLinkInActive\">Rope<></a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Attributes</div>\n");
document.write("<div id=\"divID1129\" class=\"leftMenuInActive\"><a id=\"aID1129\" href=\"#\" OnMouseOver=\"link('_member','Rope7578827',this)\" class=\"leftMenuLinkInActive\">Rope</a></div>\n");
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
