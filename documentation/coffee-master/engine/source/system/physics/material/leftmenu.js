function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6393\" class=\"headerLeftMenuInActive\"><a id=\"aID6393\" href=\"#\" OnMouseOver=\"link('_dir','material0',this)\" class=\"leftMenuLinkHeadInActive\">material</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID910\" class=\"leftMenuInActive\"><a id=\"aID910\" href=\"#\" OnMouseOver=\"link('_class','Material14855',this)\" class=\"leftMenuLinkInActive\">Material</a></div>\n");
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
