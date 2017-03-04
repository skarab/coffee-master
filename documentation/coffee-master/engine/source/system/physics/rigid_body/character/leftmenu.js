function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6398\" class=\"headerLeftMenuInActive\"><a id=\"aID6398\" href=\"#\" OnMouseOver=\"link('_dir','character0',this)\" class=\"leftMenuLinkHeadInActive\">character</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID917\" class=\"leftMenuInActive\"><a id=\"aID917\" href=\"#\" OnMouseOver=\"link('_class','Character14855',this)\" class=\"leftMenuLinkInActive\">Character</a></div>\n");
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
