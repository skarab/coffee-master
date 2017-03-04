function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6436\" class=\"headerLeftMenuInActive\"><a id=\"aID6436\" href=\"#\" OnMouseOver=\"link('_dir','resource0',this)\" class=\"leftMenuLinkHeadInActive\">resource</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID976\" class=\"leftMenuInActive\"><a id=\"aID976\" href=\"#\" OnMouseOver=\"link('_class','PropertyResource49249',this)\" class=\"leftMenuLinkInActive\">PropertyResource</a></div>\n");
document.write("<div id=\"divID977\" class=\"leftMenuInActive\"><a id=\"aID977\" href=\"#\" OnMouseOver=\"link('_class','PropertyResourceProperty49249',this)\" class=\"leftMenuLinkInActive\">PropertyResourceProperty</a></div>\n");
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
