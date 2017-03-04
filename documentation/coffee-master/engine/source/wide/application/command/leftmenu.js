function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6412\" class=\"headerLeftMenuInActive\"><a id=\"aID6412\" href=\"#\" OnMouseOver=\"link('_dir','command0',this)\" class=\"leftMenuLinkHeadInActive\">command</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID934\" class=\"leftMenuInActive\"><a id=\"aID934\" href=\"#\" OnMouseOver=\"link('_class','ApplicationCommand3886',this)\" class=\"leftMenuLinkInActive\">ApplicationCommand</a></div>\n");
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
