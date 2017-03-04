function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6264\" class=\"headerLeftMenuInActive\"><a id=\"aID6264\" href=\"#\" OnMouseOver=\"link('_dir','string0',this)\" class=\"leftMenuLinkHeadInActive\">string</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID724\" class=\"leftMenuInActive\"><a id=\"aID724\" href=\"#\" OnMouseOver=\"link('_class','String39014',this)\" class=\"leftMenuLinkInActive\">String</a></div>\n");
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
