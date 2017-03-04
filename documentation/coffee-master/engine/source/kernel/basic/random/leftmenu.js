function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6290\" class=\"headerLeftMenuInActive\"><a id=\"aID6290\" href=\"#\" OnMouseOver=\"link('_dir','random0',this)\" class=\"leftMenuLinkHeadInActive\">random</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Functions</div>\n");
document.write("<div id=\"divID2291\" class=\"leftMenuInActive\"><a id=\"aID2291\" href=\"#\" OnMouseOver=\"link('_member','GetRandom815054086',this)\" class=\"leftMenuLinkInActive\">GetRandom</a></div>\n");
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
