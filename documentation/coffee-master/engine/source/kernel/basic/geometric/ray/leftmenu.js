function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6277\" class=\"headerLeftMenuInActive\"><a id=\"aID6277\" href=\"#\" OnMouseOver=\"link('_dir','ray0',this)\" class=\"leftMenuLinkHeadInActive\">ray</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID737\" class=\"leftMenuInActive\"><a id=\"aID737\" href=\"#\" OnMouseOver=\"link('_class','Ray339014',this)\" class=\"leftMenuLinkInActive\">Ray3</a></div>\n");
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
