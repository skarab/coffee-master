function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6375\" class=\"headerLeftMenuInActive\"><a id=\"aID6375\" href=\"#\" OnMouseOver=\"link('_dir','material0',this)\" class=\"leftMenuLinkHeadInActive\">material</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID882\" class=\"leftMenuInActive\"><a id=\"aID882\" href=\"#\" OnMouseOver=\"link('_class','Material54809',this)\" class=\"leftMenuLinkInActive\">Material</a></div>\n");
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
