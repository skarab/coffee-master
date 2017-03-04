function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6462\" class=\"headerLeftMenuInActive\"><a id=\"aID6462\" href=\"#\" OnMouseOver=\"link('_dir','clip_board0',this)\" class=\"leftMenuLinkHeadInActive\">clip_board</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1039\" class=\"leftMenuInActive\"><a id=\"aID1039\" href=\"#\" OnMouseOver=\"link('_class','ClipBoard49249',this)\" class=\"leftMenuLinkInActive\">ClipBoard</a></div>\n");
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
