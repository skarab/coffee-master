function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6265\" class=\"headerLeftMenuInActive\"><a id=\"aID6265\" href=\"#\" OnMouseOver=\"link('_dir','text0',this)\" class=\"leftMenuLinkHeadInActive\">text</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID725\" class=\"leftMenuInActive\"><a id=\"aID725\" href=\"#\" OnMouseOver=\"link('_class','Text39014',this)\" class=\"leftMenuLinkInActive\">Text</a></div>\n");
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
