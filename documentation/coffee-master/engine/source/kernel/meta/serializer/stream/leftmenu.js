function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6310\" class=\"headerLeftMenuInActive\"><a id=\"aID6310\" href=\"#\" OnMouseOver=\"link('_dir','stream0',this)\" class=\"leftMenuLinkHeadInActive\">stream</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID789\" class=\"leftMenuInActive\"><a id=\"aID789\" href=\"#\" OnMouseOver=\"link('_class','Stream53261',this)\" class=\"leftMenuLinkInActive\">Stream</a></div>\n");
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
