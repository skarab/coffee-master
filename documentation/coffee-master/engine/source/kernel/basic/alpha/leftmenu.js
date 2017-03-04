function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6509\" class=\"headerLeftMenuInActive\"><a id=\"aID6509\" href=\"#\" OnMouseOver=\"link('_dir','alpha0',this)\" class=\"leftMenuLinkHeadInActive\">alpha</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6264\" class=\"leftMenuInActive\"><a id=\"aID6264\" href=\"#\" OnMouseOver=\"link('_dir','string/string0',this)\" class=\"leftMenuLinkInActive\">string</a></div>\n");
document.write("<div id=\"divID6265\" class=\"leftMenuInActive\"><a id=\"aID6265\" href=\"#\" OnMouseOver=\"link('_dir','text/text0',this)\" class=\"leftMenuLinkInActive\">text</a></div>\n");
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
